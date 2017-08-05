#-*- coding: UTF-8 -*-

import mysql.connector
from bs4 import BeautifulSoup
import requests
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')

MYSQL_HOSTS = '127.0.0.1'
MYSQL_USER = 'root'
MYSQL_PASSWORD = 'huwei351'
MYSQL_PORT = '3306'
MYSQL_DB = 'dlt'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

def update_database(qid):
    res = -2
    url='http://www.lottery.gov.cn/historykj/history.jspx?_ltype=dlt'
    html = requests.get(url)
    content=BeautifulSoup(html.text, 'lxml')
    rows = content.findAll('tr')
    for row in rows:
        if re.search("blue", str(row)):
            columns = row.findAll('td')
            rid = re.findall('>(\d+)<', str(columns[0]))[0]
            datestr = str(columns[19])
            date = re.findall('>(\S+)<', str(columns[19]))[0]
            rb1 = re.findall('>(\d+)<', str(columns[1]))[0]
            rb2 = re.findall('>(\d+)<', str(columns[2]))[0]
            rb3 = re.findall('>(\d+)<', str(columns[3]))[0]
            rb4 = re.findall('>(\d+)<', str(columns[4]))[0]
            rb5 = re.findall('>(\d+)<', str(columns[5]))[0]
            bb1 = re.findall('>(\d+)<', str(columns[6]))[0]
            bb2 = re.findall('>(\d+)<', str(columns[7]))[0]
            dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'bb1':bb1, 'bb2':bb2}
            if (rid > bytes(qid)):
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", bb1=" + bb1 + ", bb2=" + bb2)
                save_result_into_database(dict)
                res = 0
    return res

def save_result_into_database(dict):
    date = dict['date']
    ret = select_title(date)
    if ret[0] ==1:
        print('result already exsisted')
    else:
        rid = dict['rid']
        rb1 = dict['rb1']
        rb2 = dict['rb2']
        rb3 = dict['rb3']
        rb4 = dict['rb4']
        rb5 = dict['rb5']
        bb1 = dict['bb1']
        bb2 = dict['bb2']
        insert_dlt_result(rid,date,rb1,rb2,rb3,rb4,rb5,bb1,bb2)
        print('starting save results')

def insert_dlt_result(rid,date,rb1,rb2,rb3,rb4,rb5,bb1,bb2):
    sql = 'INSERT INTO ssq_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`bb1`,`bb2`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(bb1)s,%(bb2)s)'
    value = {
        'rid':rid,
        'date':date,
        'rb1':rb1,
        'rb2':rb2,
        'rb3':rb3,
        'rb4':rb4,
        'rb5':rb5,
        'bb1':bb1,
        'bb2':bb2,
    }
    cur.execute(sql,value)
    cnx.commit()

def select_title(date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
    sql= 'SELECT EXISTS (SELECT 1 FROM dlt_result WHERE date = %(date)s)'
    value = {
        'date':date
    }
    cur.execute(sql,value)
    return  cur.fetchall()[0]
                                                            