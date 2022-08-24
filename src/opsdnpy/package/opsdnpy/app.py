
# Here we provide 2 decorators for make a class controller app and a method event handler.

def controller_app(cls):
    cls.handlers = {}

    def dispatch(self, dp, ev_name, msg):
        if ev_name in self.handlers:
            for method in self.handlers[ev_name]:
                getattr(self, method)(dp, msg)

    # Find all methods with attribtue _evs, and add them to the handler map.
    cls.dispatch = dispatch
    for method_name in dir(cls):
        method = getattr(cls, method_name)
        if hasattr(method, '_evs'):
            for ev in method._evs:
                if ev not in  cls.handlers:
                    cls.handlers[ev] = []
                cls.handlers[ev].append(method_name)
    return cls

# This decorator will add _evs attribute to a method, where we will put event names to it.
def set_ev_handler(ev_cls):
    def wrapper(func):
        if not hasattr(func, '_evs'):
            func._evs = []
        func._evs.append(ev_cls.__name__)
        return func
    return wrapper
