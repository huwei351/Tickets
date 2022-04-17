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
MYSQL_DB = 'ssq'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

def update_database(qid):
    '''
    url='http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html'
    html = requests.get(url) 
    content=BeautifulSoup(html.text, 'lxml')
    rows = content.findAll('tr')
    for row in rows:
        if re.search("em class", str(row)):
            columns = row.findAll('td')
            rid = re.findall(r'(\d+)', str(columns[1]))[0]
            date = str(columns[0])[19:29]
            balls = re.findall(r'(\d+)', str(columns[2]))
            rb1 = balls[1]
            rb2 = balls[2]
            rb3 = balls[3]
            rb4 = balls[4]
            rb5 = balls[5]
            rb6 = balls[6]
            bb = balls[7]
            print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
            dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
            if rid > qid:
                save_result_into_database(dict)
'''
    url = 'https://datachart.500.com/ssq/history/newinc/history.php?limit=100&sort=0'
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
        rb6 = td[6].text
        bb = td[7].text
        date = td[15].text
        print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
        dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
        if rid > qid:
            save_result_into_database(dict)

def start_spider():
    '''
    #theme_url='http://shuangseqiu.cjcp.com.cn/kaijiang/'#爬虫开始的页面
    theme_url='http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html'
    html = requests.get(theme_url)
    print(html.status_code)
    page=BeautifulSoup(html.text, 'lxml').find('p', class_='pg')#找出每个区域最大的页数，然后遍历
    max_page = re.findall('<strong>(\d+)<', str(page))[0]
    print(max_page)
    #bashurl = 'http://www.cjcp.com.cn/ajax_kj.php?jsoncallback=jsonp1500982504171&ssq_type=page&pagenum='
    bashurl = 'http://kaijiang.zhcw.com/zhcw/html/ssq/list_'
    for num in range(1,int(max_page)+1):
        url = bashurl+str(num)+'.html'
        print(url)
        response=requests.get(url)
        content=BeautifulSoup(response.text, 'lxml')
        rows = content.findAll('tr')
        for row in rows:
            if re.search("em class", str(row)):
                columns = row.findAll('td')
                rid = re.findall(r'(\d+)', str(columns[1]))[0]
                date = str(columns[0])[19:29]
                balls = re.findall(r'(\d+)', str(columns[2]))
                rb1 = balls[1]
                rb2 = balls[2]
                rb3 = balls[3]
                rb4 = balls[4]
                rb5 = balls[5]
                rb6 = balls[6]
                bb = balls[7]
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
                dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
                save_result_into_database(dict)
'''
    url = 'https://datachart.500.com/ssq/history/newinc/history.php?start=03001&end=22041'
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
        rb6 = td[6].text
        bb = td[7].text
        date = td[15].text
        print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
        dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
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
        rb6 = dict['rb6']
        bb = dict['bb']
        insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb)
        print('starting save results')

def insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb):
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

def select_title(date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
    sql= 'SELECT EXISTS (SELECT 1 FROM ssq_result WHERE date = %(date)s)'
    value = {
        'date':date
    }
    cur.execute(sql,value)
    return  cur.fetchall()[0]
'''
def show_table_details():
    sql='use %(table)s'
    value = {
        'table':'ssq'
    }
    cur.execute(sql,value)
    sql='SELECT * from ssq_result ORDER BY date %(order)s'
    value = {
        'order':'DESC'
    }
    cur.execute(sql,value)
'''
start_spider()
#show_table_details()

                                                              