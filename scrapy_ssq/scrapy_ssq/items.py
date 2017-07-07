# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class ScrapySsqItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    rid = scrapy.Field()
    date = scrapy.Field()
    rb1 = scrapy.Field()
    rb2 = scrapy.Field()
    rb3 = scrapy.Field()
    rb4 = scrapy.Field()
    rb5 = scrapy.Field()
    rb6 = scrapy.Field()
    bb = scrapy.Field()

    pass
