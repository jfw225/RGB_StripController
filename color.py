from config import ARD
from kivy.app import App
from kivy.uix.colorpicker import ColorPicker, ColorWheel
from kivy.uix.gridlayout import GridLayout
from kivy.config import Config


_WIDTH= 800
_HEIGHT= 600
Config.set('graphics', 'width', str(_WIDTH))
Config.set('graphics', 'height', str(_HEIGHT))

class MyColorPicker(ColorPicker):
    def __init__(self, **kwargs):
        super(MyColorPicker, self).__init__(**kwargs)


    def format_color(self):
        rgba = [round(v, 2) for v in self.color]
        return [rgba[-1]] + rgba[:-1]


class ClientApp(App):
    def __init__(self):
        super(ClientApp, self).__init__()

    def build(self):
        layout = GridLayout(cols=1)

        self.clr_lower = MyColorPicker()
        self.clr_lower.bind(color=self.on_color)
        self.clr_upper = MyColorPicker()
        self.clr_upper.bind(color=self.on_color)
        layout.add_widget(self.clr_upper)
        layout.add_widget(self.clr_lower)

        return layout

    def on_color(self, instance, value):
        ClientApp.write_color(self.clr_lower.format_color() + self.clr_upper.format_color())

    @staticmethod
    def write_color(rgb : tuple["bn_low", "r_low", "g_low", "b_low", "bn_upp", "r_upp", "g_upp", "b_upp"]):
        cmd = (",".join(map(str, rgb)) + ",|").encode()
        print(cmd)
        ARD.write(cmd)



