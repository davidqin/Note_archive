require "rack"

class Redirect
  def self.call env
    if env["QUERY_STRING"] =~ /url=redirect/
      ["302", {"location" => "http://qinhru.com"}, []]
    else
      ["200", {"location" => "text/plain"}, ["ok"]]
    end
  end
end

Rack::Server.new(app: Redirect, environment: "development").start
