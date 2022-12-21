from flask import Flask,url_for,redirect,render_template,request,Response
from onem2m import *
from turbo_flask import Turbo
import threading, time
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
import io
# from pyngrok import conf,ngrok

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
# ngrok.set_auth_token("2BJ1C0e0SKkWRZwuvildXdVSyJY_MjBH2qeq16iRzBwsfRe3")
# conf.get_default().region = "in"
app = Flask(__name__)
turbo = Turbo(app)
# http_tunnel = ngrok.connect(5000)
# x = http_tunnel.__str__().split(" ")[1][1:-1]
app.config['SERVER_NAME'] = "127.0.0.1:5000"
# print(app.config['SERVER_NAME'])

@app.before_first_request
def before_first_request():
    threading.Thread(target=update).start()

def update():
    with app.app_context():
        while True:
            time.sleep(1)
            count = get_data(uri_cse+"/peopleCount/count/la")
            light = get_data(uri_cse+"/Light/level/la")
            data=count['m2m:cin']['con']
            data2=light['m2m:cin']['con']
            plot_png()
            # redirect(url_for('plot_png'))
            turbo.push(turbo.replace(render_template('dynamic.html',people=data,light=data2), 'load'))

@app.route('/',methods=['GET','POST'])
def base():
    if request.method == 'POST':
        if request.form['but'] == 'on':
            create_data_cin(uri_cse+"/userInput/input/",1)
        elif request.form['but'] == 'off':
            create_data_cin(uri_cse+"/userInput/input/",2)
        else:
            create_data_cin(uri_cse+"/userInput/input/",0)
    count = get_data(uri_cse+"/peopleCount/count/la")
    light = get_data(uri_cse+"/Light/level/la")
    data=count['m2m:cin']['con']
    data2=light['m2m:cin']['con']
    return render_template('smartbulb.html',people=data,light=data2)

@app.route('/plot.png')
def plot_png():
    fig = create_figure()
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    return Response(output.getvalue(), mimetype='image/png')

def create_figure():
    light = get_data(uri_cse+"/Light/level/?rcn=4")
    light = light['m2m:cnt']['m2m:cin']
    fig = Figure()
    axis = fig.add_subplot(1,1,1)
    ys = range(4)
    xs = [0,0,0,0]
    for i in light:
        xs[int(i['con'])] += 1.8
    for i in range(len(xs)):
        xs[i] = xs[i]/60
    axis.bar(ys,xs,color=['lightgreen','paleturquoise','orange','orangered'])
    axis.set_xticks([0,1,2,3])
    axis.set_xlabel('Mode of Bulb')
    axis.set_ylabel('Time (in minutes)')
    axis.title.set_text('Power consumption of Bulb')
    return fig

if __name__ == '__main__':
    app.run()