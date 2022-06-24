import opsdn


class OpTimer:
    MIN_INTRPT_CODE = 1000
    MAX_INTRPT_CODE = 10000
    timers = dict()

    def __init__(self):
        pass

    def get_next_available_intrpt_code(self):
        for i in range(self.MIN_INTRPT_CODE, self.MAX_INTRPT_CODE):
            if i not in self.timers:
                return i

    def set_op_timer(self, time, callback, user_data):
        code = self.get_next_available_intrpt_code()
        self.timers[code] = (callback, user_data)
        opsdn.intrpt_schedule_self(time, code)
        # LOG.info('set_op_timer: %s', self.timers)

    def timer_timeout(self, code):
        # 有定时器到时间了
        if code in self.timers:
            callback, user_data = self.timers[code]
            callback(user_data)
            self.timers.pop(code)
        return 'ok'
