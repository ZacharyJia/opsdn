

def controller_app(cls):
    cls.handlers = {}

    def dispatch(self, dp, ev_name, msg):
        if ev_name in self.handlers:
            for method in self.handlers[ev_name]:
                getattr(self, method)(dp, msg)

    cls.dispatch = dispatch
    for method_name in dir(cls):
        method = getattr(cls, method_name)
        if hasattr(method, '_evs'):
            for ev in method._evs:
                if ev not in  cls.handlers:
                    cls.handlers[ev] = []
                cls.handlers[ev].append(method_name)
    return cls


def set_ev_handler(ev_cls):
    def wrapper(func):
        if not hasattr(func, '_evs'):
            func._evs = []
        func._evs.append(ev_cls.__name__)
        return func
    return wrapper
