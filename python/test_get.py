class B(object):
    def __getattr__(self, method):
        return "Wrong Record: method %s" % method




if __name__ == '__main__':
    b = B()
    print b.a()
