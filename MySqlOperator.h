#ifndef MYSQL_OPERATOR_H
#define MYSQL_OPERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include <mysql/mysql.h>


#define HOST "localhost"
#define PORT "3306"
#define USER "root"
#define PASSWORD  "huwei351"
#define DATABASE "ssq"
#define CHARSET "utf8"

#define TABLE_SSQ "ssq"
#define TABLE_DLT "dlt"

#define FIELD_RID "rid"
#define FIELD_DATE "date"
#define FIELD_RB_FIRST "rb1"
#define FIELD_RB_SECOND "rb2"
#define FIELD_RB_THIRD "rb3"
#define FIELD_RB_FOURTH "rb4"
#define FIELD_RB_FIFTH "rb5"
#define FIELD_RB_SIXTH "rb6"
#define FIELD_BB "bb"

class MySqlOperator
{
    public:

        MYSQL mysql;

        MySqlOperator() {
        }

        ~MySqlOperator() {
        }


        int ConnMySQL(char *host, char * port, char * Db, char * user, char* passwd, char * charset);

        std::string SelectData(char * table, char * field, int rmax);

        int InsertData(char * table, char * v_rid, char * v_date, char * v_rb1, char * v_rb2, char * v_rb3, char * v_rb4, char * v_rb5, char * v_rb6, char * v_bb);

        int UpdateData(char * table, char * field, char * value, char * w_field, char * w_value);

        int DeleteData(char * table, char * field, char * value);

        void CloseMySQLConn();

};

#endif
