#include "MySqlOperator.h"

VspdCToMySQL::VspdCToMySQL()
{
}

VspdCToMySQL::~VspdCToMySQL()
{
}

//初始化数据
int VspdCToMySQL::ConnMySQL(char *host, char * port , char * Db, char * user, char* passwd, char * charset, char * Msg)
{
    if(mysql_init(&mysql) == NULL) {
        Msg = "inital mysql handle error";
        return 1;
    }

    if(mysql_real_connect(&mysql, host, user, passwd, Db, 0, NULL, 0) == NULL) {
        Msg = "Failed to connect to database: Error";
        return 1;
    }

    if(mysql_set_character_set(&mysql, "GBK") != 0) {
        Msg = "mysql_set_character_set Error";
        return 1;
    }

    return 0;
}

//查询数据
string VspdCToMySQL::SelectData(char * SQL, int Cnum, char * Msg)
{
    MYSQL_ROW m_row;
    MYSQL_RES *m_res;
    char sql[2048];
    sprintf(sql, SQL);
    int rnum = 0;
    char rg = 0x06;//行隔开
    char cg = {0x05};//字段隔开

    if(mysql_query(&mysql, sql) != 0) {
        Msg = "select ps_info Error";
        return "";
    }

    m_res = mysql_store_result(&mysql);

    if(m_res == NULL) {
        Msg = "select username Error";
        return "";
    }

    string str("");

    while(m_row = mysql_fetch_row(m_res)) {
        for(int i = 0; i < Cnum; i++) {
            str += m_row[i];
            str += rg;
        }

        str += rg;
        rnum++;
    }

    mysql_free_result(m_res);
    return str;
}

//插入数据
int VspdCToMySQL::InsertData(char * SQL, char * Msg)
{
    char sql[2048];
    sprintf(sql, SQL);

    if(mysql_query(&mysql, sql) != 0) {
        Msg = "Insert Data Error";
        return 1;
    }

    return 0;
}

//更新数据
int VspdCToMySQL::UpdateData(char * SQL, char * Msg)
{
    char sql[2048];
    sprintf(sql, SQL);

    if(mysql_query(&mysql, sql) != 0) {
        Msg = "Update Data Error";
        return 1;
    }

    return 0;
}

//删除数据
int VspdCToMySQL::DeleteData(char * SQL, char * Msg)
{
    char sql[2048];
    sprintf(sql, SQL);

    if(mysql_query(&mysql, sql) != 0) {
        Msg = "Delete Data error";
        return 1;
    }

    return 0;
}

//关闭数据库连接
void VspdCToMySQL::CloseMySQLConn()
{
    mysql_close(&mysql);
}


6、 在main函数，（如果是其他工程级不是main了，可能是一个按钮里面的代码块）添加      一些代码，添加之后如下：
#include "stdafx.h"
#include "VspdCTOMySQL.h"

int main(int argc, char* argv[])
{
    char* host = "MYSQL服务器IP";
    char* user = "root";
    char* port = "3306";
    char* passwd = "用户密码";
    char* dbname = "数据库名称";
    char* charset = "GBK";//支持中文
    char* Msg = "";//消息变量
    //初始化
    VspdCToMySQL * vspdctomysql = new VspdCToMySQL;

    if(vspdctomysql->ConnMySQL(host, port, dbname, user, passwd, charset, Msg) == 0)
    { printf("连接成功/r/n"); }
    else
    { printf(Msg); }

    //查询
    char * SQL = "SELECT ids,username,passwd,address FROM vcaccesstest";
    string str = vspdctomysql->SelectData(SQL, 4, Msg);

    if(str.length() > 0) {
        printf("查询成功/r/n");
        printf(str.data());
        printf("/r/n");
    } else {
        printf(Msg);
    }

    //插入
    SQL = "insert into vcaccesstest(ids,username,passwd,address) values(4,'我的','123210','测试地址')";

    if(vspdctomysql->InsertData(SQL, Msg) == 0)
    { printf("插入成功/r/n"); }

    //更新
    SQL = "update vcaccesstest set username = '修改了',passwd='2345' where ids = 3 ";

    if(vspdctomysql->UpdateData(SQL, Msg) == 0)
    { printf("更新成功/r/n"); }

    //删除
    SQL = "delete from vcaccesstest where ids = 3 ";

    if(vspdctomysql->DeleteData(SQL, Msg) == 0)
    { printf("删除成功/r/n"); }

    vspdctomysql->CloseMySQLConn();
    return 0;
}
