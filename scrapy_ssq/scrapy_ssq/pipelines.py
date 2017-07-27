# -*- coding: utf-8 -*-
import MySQLdb
import mysql.connector
from scrapy_ssq import settings
# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

MYSQL_HOSTS = settings.MYSQL_HOSTS
MYSQL_USER = settings.MYSQL_USER
MYSQL_PASSWORD = settings.MYSQL_PASSWORD
MYSQL_PORT = settings.MYSQL_PORT
MYSQL_DB = settings.MYSQL_DB

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

class Sql:
    @classmethod
    def insert_ssq_result(cls,rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb):
        sql = 'INSERT INTO ssq_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`rb6`,`bb`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(rb6)s,%(bb)s)'
        value = {
            'rid':rid,
            'date':date,
            'rb1':rb1,
            'rb2':rb2,
            'rb3':rb3,
            'rb4':rb4,
            'rb5':rb5,
            'rb6':rb6,
            'bb':bb,
        }
        cur.execute(sql,value)
        cnx.commit()
    @classmethod
    def select_title(cls,date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
        sql= 'SELECT EXISTS (SELECT 1 FROM ssq_result WHERE date = %(date)s)'
        value = {
            'date':date
        }
        cur.execute(sql,value)
        return  cur.fetchall()[0]


class ScrapySsqPipeline(object):
    def process_item(self, item, spider):
        date = item['date']
        ret = Sql.select_title(date)
        if ret[0] ==1:
            print('result already exsisted')
        else:
            rid = item['rid']
            rb1 = item['rb1']
            rb2 = item['rb2']
            rb3 = item['rb3']
            rb4 = item['rb4']
            rb5 = item ['rb5']
            rb6 = item['rb6']
            bb = item['bb']
            Sql.insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb)
            print('starting save results')
        return item
