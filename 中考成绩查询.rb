#coding: utf-8

require "open-uri"
require 'uri'
require 'net/https'
require 'nokogiri'

doc = Nokogiri::HTML(open("http://218.7.193.185:8080"))

params = {}

params['__VIEWSTATE'] = doc.css('#__VIEWSTATE').first.attr('value')
params['__EVENTVALIDATION'] = doc.css('#__EVENTVALIDATION').first.attr('value')

users = []
users << ['王清萌','0104020206']
users << ['孙佳星','0104020301']
users << ['董文豪','0104020308']
users << ['刘璐',  '0104020314']
users << ['刘云',  '0104020316']
users << ['芦衍明','0104020328']
users << ['王禹',  '0104020412']
users << ['汪祉彤','0104020418']
users << ['张玉娇','0104020420']
users << ['王宏明','0104020421']
users << ['戚宝富','0104020703']
users << ['马云鹏','0104020727']
users << ['夏广宇','0104020802']
users << ['张文博','0104020808']
users << ['姜虹雨','0104020811']
users << ['董铭',  '0104020813']
users << ['李宝龙','0104020819']
users << ['刘微微','0104020823']
users << ['刘浩楠','0104020825']
users << ['朱婉茹','0104020827']
users << ['李晓旭','0104020830']
users << ['阎文',  '0104020915']
users << ['苏德文','0104020919']
users << ['路嘉财','0104021001']
users << ['薛晴',  '0104021015']
users << ['周新国','0104021023']
users << ['于喜来','0104021102']
users << ['李佳霖','0104021103']
users << ['宁静',  '0104021108']
users << ['赫鑫',  '0104021109']
users << ['郝薪澎','0104021219']
users << ['陈海洋','0104021227']
users << ['李英',  '0104021304']
users << ['张洪亮','0104021416']

params['Button1'] = '查 询'


users.each do |user|
  params["ksxm"] = user[0]
  params["zkzh"] = user[1]
  url = URI.parse("http://218.7.193.185:8080")
  res = Net::HTTP.post_form(url, params)
  doc = Nokogiri::HTML(res.body)

  i = 0
  array = [3,5,8,10,13,15,18,20,23,25,28,30,35]
  doc.xpath('html/body/form/div/table/tr/td/table/tr/td/table/tr[6]/td/table/tr/td').each do |a|
    i += 1
    string = a.content
    string.gsub!(" ", "")
    print string,'|' if(array.include?(i))
    if i == 35
      puts ""
      i = 0
    end
  end
end