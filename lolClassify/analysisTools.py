from tkinter import *
import tkinter
from PIL import Image, ImageTk
import os
import time
import json
import shutil


class ClassifyTool:
    def __init__(self):
        pass

    def start(self, path, savePath, need):
        # 生成提示框

        self.name = None

        hint = tkinter.Tk()
        hint.title("输入姓名")
        hint.geometry('400x300')  # 窗体大小
        hint.resizable(False, False)  # 固定窗体
        tkinter.Label(hint, text="请输入姓名").pack()
        E_hint = tkinter.Entry(hint, bd=5)
        E_hint.pack()

        def but():
            if E_hint.get() != '':
                self.name = E_hint.get()
                print(self.name)
                hint.destroy()

        tkinter.Button(hint, text='确认', command=but).pack()

        hint.mainloop()

        self.curNum = 0
        self.pictureNum = 0
        self.path = path
        self.savePath = savePath
        self.pictureList = os.listdir(path)
        self.pathSize = len(self.pictureList)
        self.root = tkinter.Tk()
        self.root.title('应用程序窗口')  # 窗口标题
        self.root.resizable(False, False)  # 固定窗口大小
        windowWidth = 800  # 获得当前窗口宽
        windowHeight = 500  # 获得当前窗口高
        screenWidth, screenHeight = self.root.maxsize()  # 获得屏幕宽和高
        geometryParam = '%dx%d+%d+%d' % (windowWidth, windowHeight,
                                         (screenWidth - windowWidth) / 2,
                                         (screenHeight - windowHeight) / 2)
        self.root.geometry(geometryParam)  # 设置窗口大小及偏移坐标
        self.root.wm_attributes('-topmost', 1)  # 窗口置顶

        self.B = tkinter.Button(self.root, text="提交", command=self.press)
        self.B.pack(side=BOTTOM)

        img_open = self.getImg()
        self.label_img = tkinter.Label(self.root, image=img_open)
        self.label_img.configure(image=img_open)
        self.label_img.image = img_open
        self.label_img.place(x=0, y=0)

        b1 = tkinter.Scrollbar(self.root, width=20)
        b1.pack(side=RIGHT, fill=tkinter.Y)
        b2 = tkinter.Listbox(self.root, yscrollcommand=b1.set)
        for i in range(1, 6):
            b2.insert(tkinter.END, "=====================")
            b2.insert(tkinter.END, "费用: " + str(i) + '\n')
            b2.insert(tkinter.END, "=====================")
            for item in need[i]:
                b2.insert(tkinter.END, item[1] + " : " + str(item[0]) + '\n')
            b2.insert(tkinter.END, "")
            b2.insert(tkinter.END, "")
        b2.pack(side=tkinter.RIGHT, fill=tkinter.BOTH)
        b1.config(command=b2.yview)

        self.E = tkinter.Entry(self.root, bd=5)
        self.E.pack(side=BOTTOM)
        self.E.bind('<Return>', self.press)

        self.root.mainloop()

    def press(self):
        text = self.E.get()
        self.E.delete(0, 1024)
        souPath = ""
        desPath = ""
        if text == '':
            souPath = self.path + '/' + self.pictureList[self.curNum - 1]
            desPath=self.savePath + '/' + self.name + '_' + str(time.time()) +\
                '_' + str(self.pictureNum) + '_' + str(-1) +\
                (self.pictureList[self.curNum - 1]\
                 )[self.pictureList[self.curNum - 1].rfind('.'):]
        else:
            souPath = self.path + '/' + self.pictureList[self.curNum - 1]
            desPath=self.savePath + '/' + self.name + '_' + str(time.time()) +\
                '_' + str(self.pictureNum) + '_' + text +\
                (self.pictureList[self.curNum - 1]\
                 )[self.pictureList[self.curNum - 1].rfind('.'):]
            self.pictureNum += 1
        shutil.move(souPath, desPath)
        print("\033[0;31;40mSave in:\033[0m")
        print(desPath)

        if self.curNum >= self.pathSize:
            self.root.destroy()
            return None
        img_open = self.getImg()
        self.label_img.configure(image=img_open)
        self.label_img.image = img_open

    def getImg(self):
        try:
            while self.curNum < self.pathSize and (
                    os.path.isdir(self.path + '/' +
                                  self.pictureList[self.curNum])
                    or self.pictureList[self.curNum].startswith('.')):
                self.curNum += 1
            if self.curNum >= self.pathSize:
                self.root.destroy()
                return None
            img_open = ImageTk.PhotoImage(
                Image.open(self.path + '/' + self.pictureList[self.curNum]))
            print("\033[0;32;40mGet From:\033[0m")
            print(self.path + '/' + self.pictureList[self.curNum])
            self.curNum += 1
            return img_open
        except:
            pass


if __name__ == "__main__":
    path = r"./picture"
    savePath = r"./res"
    ct = ClassifyTool()
    with open(r"./information.json", 'r') as f:
        data = json.load(f)
        need = {}
        for key, values in data.items():
            if data[key]["Cost"] in need:
                need[data[key]["Cost"]].append((key, data[key]["HeroName"][1]))
            else:
                need[data[key]["Cost"]] = [(key, data[key]["HeroName"][1])]
            #print(need)
        #print(HeroInfo)
        ct.start(path, savePath, need)
