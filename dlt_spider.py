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
MYSQL_PASSWORD = '123456'
MYSQL_PORT = '3306'
MYSQL_DB = 'dlt'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)


def start_spider():
    '''
    theme_url='http://www.lottery.gov.cn/historykj/history.jspx?_ltype=dlt'
    html = requests.get(theme_url)
    print(html.status_code)
    page=BeautifulSoup(html.text, 'lxml').find('div', class_='page')#找出每个区域最大的页数，然后遍历
    max_page = re.findall('条记录 1/(\d+)', str(page))[0]
    print(max_page)
    bashurl = 'http://www.lottery.gov.cn/historykj/history_'
    for num in range(1,int(max_page)+1):
        url = bashurl+str(num)+'.jspx?_ltype=dlt'
        print(url)
        response=requests.get(url)
        content=BeautifulSoup(response.text, 'lxml')
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
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", bb1=" + bb1 + ", bb2=" + bb2)
                dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'bb1':bb1, 'bb2':bb2}
                save_result_into_database(dict)
    '''
    url = 'http://datachart.500.com/dlt/history/newinc/history.php?start=07001&end=22041'
    html = requests.get(url)
    html.encoding = 'utf-8'
    soup = BeautifulSoup(html.text, "html.parser")
    tbody = soup.find('tbody', id="tdata")
    tr = tbody.find_all('tr')
    lens = len(tr)
    td = tr[0].find_all('td')
    for page in range(0, lens):
        td = tr[page].find_all('td')
        rid = td[0].text
        rb1 = td[1].text
        rb2 = td[2].text
        rb3 = td[3].text
        rb4 = td[4].text
        rb5 = td[5].text
        bb1 = td[6].text
        bb2 = td[7].text
        date = td[14].text
        print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", bb1=" + bb1 + ", bb2=" + bb2)
        dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'bb1':bb1, 'bb2':bb2}
        save_result_into_database(dict)

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
    sql = 'INSERT INTO dlt_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`bb1`,`bb2`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(bb1)s,%(bb2)s)'
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



start_spider()


                                                              