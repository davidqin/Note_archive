import threading
from paste.request import parse_formvars
from paste.response import HeaderDict

webinfo = threading.local()

class Request(object):
    def __init__(self, environ):
        self.environ = environ
        self.fields = parse_formvars(environ)

class Response(object):
    def __init__(self):
        self.headers = HeaderDict(
            {'content-type': 'text/html'})

class Root(object):

    # The "index" method:
    def __call__(self):
        return '''
        <form action="welcome">
        Name: <input type="text" name="name">
        <input type="submit">
        </form>
        '''

    def welcome(self, name):
        return 'Hello %s!' % name

    def rss(self):
        webinfo.response.headers['content-type'] = 'text/xml'


class ObjectPublisher(object):

    def __init__(self, root):
        self.root = root

    def __call__(self, environ, start_response):
        webinfo.request = Request(environ)
        webinfo.response = Response()
        obj = self.find_object(self.root, environ)
        response_body = obj(**dict(webinfo.request.fields))
        start_response('200 OK', webinfo.response.headers.items())
        return [response_body]

    def find_object(self, obj, environ):
        path_info = environ.get('PATH_INFO', '')
        if path_info == '/favicon.ico':
            return

        print "path_info %s" % path_info
        if not path_info or path_info == '/':
            # We've arrived!
            return obj
        # PATH_INFO always starts with a /, so we'll get rid of it:
        path_info = path_info.lstrip('/')
        # Then split the path into the "next" chunk, and everything
        # after it ("rest"):
        parts = path_info.split('/', 1)
        next = parts[0]
        if len(parts) == 1:
            rest = ''
        else:
            rest = '/' + parts[1]
        # Hide private methods/attributes:
        assert not next.startswith('_')
        # Now we get the attribute; getattr(a, 'b') is equivalent
        # to a.b...
        next_obj = getattr(obj, next)
        # Now fix up SCRIPT_NAME and PATH_INFO...
        environ['SCRIPT_NAME'] += '/' + next
        environ['PATH_INFO'] = rest
        # and now parse the remaining part of the URL...
        return self.find_object(next_obj, environ)

app = ObjectPublisher(Root())

if __name__ == '__main__':
    from paste import httpserver
    httpserver.serve(app, host='127.0.0.1', port='8080')
