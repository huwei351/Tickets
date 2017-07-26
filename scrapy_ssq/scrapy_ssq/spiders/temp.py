#-*- coding: UTF-8 -*-

import scrapy
from bs4 import BeautifulSoup
import requests
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')
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

                                                              