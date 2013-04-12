require "rack"

class Redirect
  def self.call env
    request = Rack::Request.new(env)
    response = Rack::Response.new("OK")
    response.redirect("http://qinhru.com") if request.params["url"]
    response
  end
end

Rack::Server.new(app: Redirect).start
