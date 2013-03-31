require 'net/https'
require 'uri'

uri = URI.parse('https://api.weibo.com/2/short_url/shorten.json?source=17885274&url_long=http://www.baidu.com')

http = Net::HTTP.new(uri.host, uri.port)

http.use_ssl = true if uri.scheme == "https"  # enable SSL/TLS
http.verify_mode = OpenSSL::SSL::VERIFY_NONE #这个也很重要

http.start {
  http.request_get(uri.path + "?" + uri.query) {|res|
    print res.body
  }
}
