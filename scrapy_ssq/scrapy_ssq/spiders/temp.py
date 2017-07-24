#-*- coding: UTF-8 -*-

import scrapy
from bs4 import BeautifulSoup
import requests
import re
'''
theme_url='http://shuangseqiu.cjcp.com.cn/kaijiang/'#爬虫开始的页面
html = requests.get(theme_url)
print(html.status_code)
page=BeautifulSoup(html.text, 'lxml').find('div', class_='n_dm_page')#找出每个区域最大的页数，然后遍历
print (page)
for p in page:
	if p:
		max_page = re.findall('span>/(\d+)页次', str(p))
		for max in max_page:
			if max:
				print(max)
				bashurl = str(html.url)[:-1]
				print(bashurl)
				for num in range(1,int(max)+1):
			              	url = bashurl+str(num)+'/'
			              	print(url)
			              	response=requests.get(url)
			              	print(response.status_code)
			              	content=BeautifulSoup(response.text, 'lxml')
'''
theme_url='http://shuangseqiu.cjcp.com.cn/kaijiang/'#爬虫开始的页面
html = requests.get(theme_url)
content=BeautifulSoup(html.text, 'lxml')
tables = content.findAll('table')#找到所在的标签里
for table in tables:
    if re.search("kjjg_table", str(table)):
        rows = table.findAll('tr')
        for row in rows:
            if re.search("双色球开奖结果第", str(row)):
                print("------------ result -----------")
                columns = row.findAll('td')

                rid = re.findall(r'(\d+)', str(columns[0]))[0]

                date = str(columns[1])[4:14]

                rbs = re.findall('class="hm_bg">(\d+)<', str(columns[2]))
                rb1 = rbs[0]
                rb2 = rbs[1]
                rb3 = rbs[2]
                rb4 = rbs[3]
                rb5 = rbs[4]
                rb6 = rbs[5]
                bb = re.findall('class="lqhm_bg">(\d+)<', str(columns[2]))[0]
                print("rid=" + rid + ", date=" + date + ", rb1=" + rbs[0] + ", rb2=" + rbs[1] + ", rb3=" + rbs[2] + ", rb4=" + rbs[3] + ", rb5=" + rbs[4] + ", rb6=" + rbs[5] + ", bb=" + bb)
 