import scrapy
from bs4 import BeautifulSoup
from scrapy.http import Request
from scrapy_ssq.items import ScrapySsqItem
import requests
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')


class myspider(scrapy.Spider):
    name = 'ssq'
    allowed_domains =['kaijiang.zhcw.com']


    def start_requests(self):
        theme_url = 'http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html'#爬虫开始的页面
        yield Request(theme_url,self.parse)#对每个链接调用parse函数
    def parse(self, response):
        page = BeautifulSoup(response.text, 'lxml').find('p', class_='pg')#找出最大的页数，然后遍历
        max_page = re.findall('<strong>(\d+)<', str(page))[0]
        print("max_page = " + max_page)
        bashurl = 'http://kaijiang.zhcw.com/zhcw/html/ssq/list_'
        for num in range(1,int(max_page)+1):
            url = bashurl+str(num)+'.html'
            print(url)
            yield Request(url,callback=self.get_message)
    def get_message(self,response):
        item = ScrapySsqItem()
        content = BeautifulSoup(response.text, 'lxml')
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
            item['rid'] = rid
            item['date'] = date
            item['rb1'] = rb1
            item['rb2'] = rb2
            item['rb3'] = rb3
            item['rb4'] = rb4
            item['rb5'] = rb5
            item['rb6'] = rb6
            item['bb'] = bb
            yield item
