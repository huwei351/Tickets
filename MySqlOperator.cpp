#include "MySqlOperator.h"


//Init MySQL
int MySqlOperator::ConnMySQL(char *host, char * port , char * Db, char * user, char* passwd, char * charset)
{
    int res = 0;

    if(mysql_init(&mysql) == NULL) {
        printf("inital mysql handle error");
        res = -1;
    }

    if(mysql_real_connect(&mysql, host, user, passwd, Db, atoi(port), NULL, 0) == NULL) {
        printf("Failed to connect to database: Error");
        res = -2;
    }

    /*
        res = mysql_set_character_set(&mysql, "GBK") ;

        if(!res) {
            printf("mysql_set_character_set Error\n");
        }
    */
    return res;
}

//Query data
std::string MySqlOperator::SelectData(char * table, char * field, int rmax, char* order)
{
    MYSQL_ROW m_row;
    MYSQL_RES *m_res;
    MYSQL_FIELD *m_field;
    std::string str = "";
    int rnum , cnum;
    char sql[2048];

    if(field == NULL)
    { sprintf(sql, "select * from %s order by date %s", table, order); }
    else
    { sprintf(sql, "select %s from %s order by date %s", field, table, order); }

    int res = mysql_query(&mysql, sql);
    //printf("mysql_query: sql=\"%s\", res=%d\n", sql, res);

    if(res) {
        mysql_error(&mysql);
        return "";
    } else {
        m_res = mysql_store_result(&mysql);

        if(m_res == NULL) {
            mysql_error(&mysql);
            return "";
        }

        cnum = mysql_num_fields(m_res);
        rnum = mysql_num_rows(m_res);
        //printf("column_num = %d, row_num = %d\n", cnum, rnum);

        for(int i = rnum - rmax; i < rnum; i++) {
            m_row = mysql_fetch_row(m_res);

            for(int j = 0; j < cnum; j++) {
                str += m_row[j];
                str += COLUMN_G;
            }

            str += ROW_G;
        }

        mysql_free_result(m_res);
    }

    return str;
}

//Insert data
int MySqlOperator::InsertData(char * table, char * v_rid, char * v_date, char * v_rb1, char * v_rb2, char * v_rb3, char * v_rb4, char * v_rb5, char * v_rb6, char * v_bb)
{
    char sql[2048];
    sprintf(sql, "insert into %s values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')", table, v_rid, v_date, v_rb1, v_rb2, v_rb3, v_rb4, v_rb5, v_rb6, v_bb);
    int res = mysql_query(&mysql, sql);

    if(res != 0) {
        mysql_error(&mysql);
    }

    return res;
}

//Update data
int MySqlOperator::UpdateData(char * table, char * field, char * value, char * w_field, char * w_value)
{
    char sql[2048];
    sprintf(sql, "update %s set %s = \'%s\' where %s = \'%s\'", table, field, value, w_field, w_value);
    int res = mysql_query(&mysql, sql);

    if(res != 0) {
        mysql_error(&mysql);
    }

    return res;
}

//Delete data
int MySqlOperator::DeleteData(char * table, char * field, char * value)
{
    char sql[2048];
    sprintf(sql, "delete from %s where %s = %s", table, field, value);
    int res = mysql_query(&mysql, sql);

    if(res != 0) {
        mysql_error(&mysql);
    }

    return res;
}

//Get table length
int MySqlOperator::getDatabaseTableLength(char * table)
{
    MYSQL_RES *m_res;
    int rnum , cnum;
    char sql[2048];
    sprintf(sql, "select * from %s", table);
    int res = mysql_query(&mysql, sql);
    printf("sql=%s, res=%d\n", sql, res);

    if(res) {
        mysql_error(&mysql);
        return 0;
    } else {
        m_res = mysql_store_result(&mysql);

        if(m_res == NULL) {
            mysql_error(&mysql);
            return 0;
        }

        cnum = mysql_num_fields(m_res);
        rnum = mysql_num_rows(m_res);
        mysql_free_result(m_res);
    }

    return rnum;
}


//Close MySQL connection
void MySqlOperator::CloseMySQLConn()
{
    mysql_close(&mysql);
}

