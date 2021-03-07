from tkinter import *
offset=0
offsety=20
ylim=900
d={"1":"A","2":"AA","3":"Ae","4":"AeA","5":"EE","6":"UU","7":"O"," ":"_"}
diction={"1_1":"A","1_2":"B","1_3":"C","1_4":"D","1_5":"E","1_6":"F","1_7":"G","2_1":"H","2_2":"I","2_3":"J","2_4":"K","2_5":"L","2_6":"M",
    "2_7":"N","3_1":"O","3_2":"P","3_3":"Q","3_4":"R","3_5":"S","3_6":"T","3_7":"U","4_1":"V","4_2":"W","4_3":"X","4_4":"Y","4_5":"Z"}
sentence=""

myWin=Tk()
myWin.title("Console [ @TM ]")
ht=960;wid=1280;
frm1=Frame(myWin,height=ht,width=wid)
frm1.pack()
ratioV=0.5;
ratioH=0.75;
disp = Label(frm1, text="")

def live(event):
    txt=str(event.char)
    global offset, offsety, ylim, d, sentence
    offset=offset+15
    if txt==" ":
        sentence=sentence+"_"
    else:
        sentence=sentence+txt
    if txt=='2' or txt=='3' or txt=='5' or txt=='6':
        offset=offset+4
    if txt=='4':
        offset=offset+10
    if offset>=ylim:
        offsety=offsety+30
        offset=0
    frm1_sub1.create_text(15+offset,offsety,font=('helvetica','15','bold'),text=d[txt],fill="#0BB5FF")
    if txt=='2' or txt=='3' or txt=='5' or txt=='6':
        offset=offset+4
    if txt=='4':
        offset=offset+10
    frm1_sub1.update

def getTxt(sen):
    global diction
    n=len(sen)
    x=0;sp_cnt=0;wrd="";
    while x<n:
        if sen[x]>="1" and sen[x]<="7":
            sp_cnt=0
            if x+1<n and x+2<n:
                tmp=sen[x]+sen[x+1]+sen[x+2]
                wrd+=diction[tmp]
                x+=3
            else:
                x=n+1
        else:
            sp_cnt=sp_cnt+1
            x=x+1
        if sp_cnt==3:
            wrd=wrd+"   "
            sp_cnt=0
    return wrd

def dummy(event):
    txt=getTxt(sentence);print(txt)
    widget=Label(frm1_sub2,font=('helvetica','16'),text=txt,bg="#5B646F")
    frm1_sub2.create_window(60,60,window=widget)
    frm1_sub1.update

frm1_sub1=Canvas(frm1,height=ht*ratioV,width=wid*ratioH,bg="#2D353F")
frm1_sub2=Canvas(frm1,height=ht*(1-ratioV),width=wid*ratioH,bg="#5B646F")
b1=Button(frm1_sub2,font=('helvetica','15','bold'),text="CONVERT")
b1.configure(width=8,activebackground="#0BB5FF",relief=FLAT)
b1.bind("<Button-1>",dummy)
b1Win=frm1_sub2.create_window(50,15,window=b1)
canvas=Canvas(frm1,height=ht,width=wid*(1-ratioH),bg="#00060F")
frm1_sub1.grid(row=1,column=1);frm1_sub2.grid(row=2,column=1);
canvas.grid(row=1,column=2,rowspan=2);
# --- canvas --- has instructions
canvas.create_text(160,30,font=('helvetica','16','bold'),text="RULES  TO  BE  FOLLOWED",fill='white')
canvas.create_text(175,350,font=('helvetica','12'),text="\n\nA + _ + A = A\nA + _ + AA = B\nA + _ + Ae = C\nA + _ + AeA = D\nA + _ + EE = E\nA + _ + UU = F\nA + _ + O = G\nAA + _ + A = H\nAA + _ + AA = I\nAA + _ + Ae = J\nAA + _ + AeA = K\nAA + _ + EE = L\nAA + _ + UU = M\nAA + _ + O = N\nAe + _ + A = O\nAe + _ + AA = P\nAe + _ + Ae = Q\nAe + _ + AeA = R\nAe + _ + EE = S\nAe + _ + UU = T\nAe + _ + O = U\nAeA + _ + A = V\nAeA + _ + AA = W\nAeA + _ + Ae = X\nAeA + _ + AeA = Y\nAeA + _ + EE = Z\n1 '_' b/w sounds.\n2 '_' b/w letters.\n3 '_' b/w words.",
    fill='white')
canvas.update
# --- frm1_sub1 --- has instructions
myWin.bind("<Key>",live)
# --- frm1_sub2 --- has instructions
myWin.mainloop();