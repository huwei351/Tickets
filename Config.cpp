// Config.cpp

#include "Config.h"

using namespace std;


Config::Config(string filename, string delimiter,
               string comment, string section)
    : m_Delimiter(delimiter), m_Comment(comment), m_Section(section)
{
    // Construct a Config, getting keys and values from given file
    m_Contents  = NULL;
    std::ifstream in(filename.c_str());

    if(in) { //throw File_not_found( filename );
        m_fileName = filename;
        in >> (*this);
        AddSection("default");
        MapKeyValue *pkv = m_mapSection[m_Section];

        if(pkv != NULL) {
            m_Contents = pkv;
        } else {
            m_Contents = m_mapSection["default"];
            m_Section = "default";
        }

        printf("Load Config from: %s, current setion: %s [%p]\n", filename.c_str(), m_Section.c_str(), m_Contents);
    }
}


Config::Config()
    : m_Delimiter(string(1, '=')), m_Comment(string(1, '#')), m_Section("default")
{
    // Construct a Config without a file; empty
    m_Contents = new Config::MapKeyValue();
    m_mapSection[m_Section] = m_Contents;
}



bool Config::KeyExists(const string& key) const
{
    if(m_Contents == NULL)
    { return false; }

    // Indicate whether key is found
    mapci p = m_Contents->find(key);
    return (p != m_Contents->end());
}


bool Config::AddSection(const std::string section)
{
    bool ret = false;
    mapsi p  = m_mapSection.find(section);

    if(p == m_mapSection.end()) {
        MapKeyValue *pkv = new Config::MapKeyValue();
        m_mapSection[section] =  pkv;

        if(m_Contents == NULL) {
            m_Contents = pkv;
            m_Section = section;
        }

        ret = true;
    }

    return ret;
}


bool Config::ChangeSection(const std::string section)
{
    bool ret = false;

    if(m_Contents != NULL && m_Section == section) {
        ret = true;
    } else {
        mapsi p  = m_mapSection.find(section);

        if(p != m_mapSection.end()) {
            m_Section = section;
            m_Contents = m_mapSection[section];
            ret = true;
        }
    }

    return ret;
}

/* static */
void Config::Trim(string& inout_s)
{
    if(inout_s.empty())
    { return; }

    // Remove leading and trailing whitespace
    static const char whitespace[] = " \n\t\v\r\f";
    inout_s.erase(0, inout_s.find_first_not_of(whitespace));
    inout_s.erase(inout_s.find_last_not_of(whitespace) + 1U);
}

/* static */
void Config::Split(std::string str, const char* delimiter, std::vector<std::string>& tokens)
{
    tokens.clear();
    char *p;
    char *buf = const_cast<char*>(str.c_str());
    p = strtok(buf, delimiter);

    while(p != NULL) {
        tokens.push_back(p);
        p = strtok(NULL, delimiter);
    }
}

std::ostream& operator<<(std::ostream& os, const Config& cf)
{
    for(Config::mapsci s = cf.m_mapSection.begin(); s != cf.m_mapSection.end(); ++s) {
std:
        string section = s->first;
        Config::MapKeyValue *kv = s->second;
        os << std::endl << '[' <<  section << ']' << std::endl;

        // Save a Config to os
        if(kv) {
            for(Config::mapci p = kv->begin();
                p != kv->end();
                ++p) {
                os << p->first << " " << cf.m_Delimiter << " ";
                os << p->second << std::endl;
            }
        }
    }

    return os;
}

void Config::Remove(const string& key)
{
    // Remove key and its value
    if(m_Contents)
    { m_Contents->erase(m_Contents->find(key)); }

    return;
}

bool Config::IsCommentLine(const char* szLine)
{
    return (szLine[0] == '#');
}

bool Config::IsEmptyLine(const char* szLine)
{
    int nLineSize = strlen(szLine);

    if(nLineSize == 0) {
        return true;
    } else {
        return false;
    }
}

bool Config::IsNewSection(const char* szLine)
{
    return (strchr(szLine, '[') && strchr(szLine, ']'));
}

bool Config::IsKeyValueLine(const char* szLine)
{
    return (NULL != strchr(szLine, '='));
}

bool Config::GetNewSectionContext(const char* szLine, string& strNewSectionContext)
{
    char szSectionContextBuf[MAX_SECTION_CONTEXT_BUF_SIZE] = {0};
    strNewSectionContext.clear();
    const char* pSectionContextBegin = strchr(szLine, '[');
    const char* pSectionContextEnd = strchr(szLine, ']');
    int nSectionContextLen = pSectionContextEnd - pSectionContextBegin - 1;

    if(nSectionContextLen >  MAX_SECTION_CONTEXT_BUF_SIZE)
    { return false; }

    strncpy(szSectionContextBuf, pSectionContextBegin + 1, nSectionContextLen);
    strNewSectionContext = szSectionContextBuf;
    return true;
}


std::istream& operator>>(std::istream& is, Config& cf)
{
    // Load a Config from is
    // Read in keys and values, keeping internal whitespace
    typedef string::size_type pos;
    const string& delim  = cf.m_Delimiter;  // separator
    const string& comm   = cf.m_Comment;    // comment
    const pos skip = delim.length();        // length of separator
    string nextline = "";  // might need to read ahead to see where value ends
    Config::MapKeyValue *pkv = NULL;

    while(is || nextline.length() > 0) {
        string line;
        string strCurSection;
        // Read an entire line at a time
        std::getline(is, line);

        if(cf.IsCommentLine(line.c_str()) || cf.IsEmptyLine(line.c_str())) {
            continue;
        } else if(cf.IsNewSection(line.c_str())) {
            cf.GetNewSectionContext(line.c_str(), strCurSection);
            pkv =  new Config::MapKeyValue();
            cf.m_mapSection[strCurSection] =  pkv;
            printf("add Section: %s\n", strCurSection.c_str());
            continue;
        } else { // Key -value line
            // Ignore comments
            line = line.substr(0, line.find(comm));
            // Parse the line if it contains a delimiter 'key=value'
            pos delimPos = line.find(delim);

            if(delimPos < string::npos) {
                // Extract the key and value
                string key = line.substr(0, delimPos);
                string value = line.replace(0, delimPos + skip, "");
                // Store key and value
                Config::Trim(key);
                Config::Trim(value);

                if(pkv) {
                    (*pkv)[key] = value;  // overwrites if key is repeated
                    printf("add Config:  key = %s, value = %s\n", key.c_str(), value.c_str());
                }
            }
        }
    }

    return is;
}
bool Config::FileExist(std::string filename)
{
    bool exist = false;
    std::ifstream in(filename.c_str());

    if(in)
    { exist = true; }

    return exist;
}

void Config::ReadFile(string filename, string delimiter,
                      string comment)
{
    m_Delimiter = delimiter;
    m_Comment = comment;
    std::ifstream in(filename.c_str());

    if(!in) { return; }   //throw File_not_found( filename );

    in >> (*this);

    if(m_mapSection.find(m_Section) != m_mapSection.end())
    { m_Contents = m_mapSection[m_Section]; }
}


void Config::Save(string filename)
{
    if(filename.empty())
    { filename = m_fileName; }

    std::ofstream os(filename.c_str());

    if(!os) { return; }   //throw File_not_found( filename );

    os << (*this);
}