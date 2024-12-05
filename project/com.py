import serial
import tkinter as tk

def createGui():
	root = tk.Tk()
	buttons = []
	root.resizable(False, False)
	for i in range(9):
		buttons.append(tk.Button(root, height=10, width=15))
		buttons[i].grid(row=i//3, column=i%3)
		# buttons[i].pack()
	root.bind("<Escape>", lambda x: root.destroy())
	root.mainloop()

def readserial(comport, baudrate):
	ser = serial.Serial(comport, baudrate, timeout=0.1)  
	while True:
		data = ser.readline().decode().strip()
		if data:
			print(data)
			s = data.split()
			buttons(s[1]*3 + s[2]).setText("x")

if __name__ == '__main__':
	createGui()
	readserial('/dev/ttyACM0', 9600)