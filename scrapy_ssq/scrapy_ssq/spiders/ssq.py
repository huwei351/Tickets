import scrapy
from bs4 import BeautifulSoup
from scrapy.http import Request
from scrapy_ssq.items import ScrapySsqItem
import requests
import re

class myspider(scrapy.Spider):
    name = 'ssq'
    allowed_domains =['cjcp.com.cn']



    def start_requests(self):
        theme_url = 'http://http://shuangseqiu.cjcp.com.cn/kaijiang/'#爬虫开始的页面
        yield Request(theme_url,self.parse)#对每个链接调用parse函数
    def parse(self, response):
        page = BeautifulSoup(response.text, 'lxml').find('div', class_='n_dm_page')#找出最大的页数，然后遍历
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
                            yield Request(url,callback=self.get_message)
    def get_message(self,response):
        item = ScrapySsqItem()
        content = BeautifulSoup(response.text, 'lxml')
        tables = content.findAll('table')
        for table in tables:
            if re.search("kjjg_table", str(table)):
                rows = table.findAll('tr')
                for row in rows:
                    if re.search("双色球开奖结果第", str(row)):
                        columns = row.findAll('td')
                        # find rid
                        rid = re.findall(r'(\d+)', str(columns[0]))[0]
                        item['rid'] = rid
                        # find date
                        date = str(columns[1])[4:14]
                        item['date'] = date
                        # find red and blue number
                        rbs = re.findall('class="hm_bg">(\d+)<', str(columns[2]))
                        item['rb1'] = rbs[0]
                        item['rb2'] = rbs[1]
                        item['rb3'] = rbs[2]
                        item['rb4'] = rbs[3]
                        item['rb5'] = rbs[4]
                        item['rb6'] = rbs[5]
                        bb = re.findall('class="lqhm_bg">(\d+)<', str(columns[2]))[0]
                        item['bb'] = bb   
                        print("rid=" + rid + ", date=" + date + ", rb1=" + rbs[0] + ", rb2=" + rbs[1] + ", rb3=" + rbs[2] + ", rb4=" + rbs[3] + ", rb5=" + rbs[4] + ", rb6=" + rbs[5] + ", bb=" + bb)
                        yield item
