import serial
import tkinter as tk
from tkinter import messagebox
from threading import Thread
import queue

class ArduinoGUI:
    def __init__(self):
        self.root = tk.Tk()
        self.buttons = []
        self.data_queue = queue.Queue()
        self.running = True
        self.moves_count = 0 
        
        
        self.root.resizable(False, False)
        self.root.title("Tic Tac Toe")
        
        for i in range(9):
            button = tk.Button(self.root, height=10, width=15, font=("Times New Roman", 20, "bold"))
            button.grid(row=i//3, column=i%3)
            self.buttons.append(button)
            
        self.root.bind("<Escape>", self.on_escape)
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
        
        self.serial_thread = Thread(target=self.read_serial, daemon=True)
        self.serial_thread.start()
        
        self.check_queue()
    
    def show_winner(self, winner):
        if winner == '0':
            messagebox.showinfo("Joc terminat", "O castiga!")
        elif winner == 'X':
            messagebox.showinfo("Joc terminat", "X castiga!")
        self.reset_game()
    
    def check_draw(self):
        if self.moves_count == 9:
            messagebox.showinfo("Joc terminat", "Egalitate")
            self.reset_game()
    
    def reset_game(self):
        self.moves_count = 0
        for button in self.buttons:
            button.configure(
                text="",
                state='normal'
            )
        
    def read_serial(self):
        try:
            ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0.1)
            while self.running:
                data = ser.readline().decode().strip()
                if data:
                    parts = data.split()
                    if len(parts) == 1:  # Single character - winner
                        self.data_queue.put(('WINNER', parts[0]))
                    elif len(parts) == 3:  # Move: symbol, row, col
                        try:
                            symbol = parts[0]
                            row = int(parts[1])
                            col = int(parts[2])
                            if 0 <= row < 3 and 0 <= col < 3:
                                button_index = row * 3 + col
                                self.data_queue.put(('MOVE', (symbol, button_index)))
                        except (ValueError, IndexError):
                            print("Invalid data received:", data)
        except serial.SerialException as e:
            print(f"Serial error: {e}")
        finally:
            if 'ser' in locals():
                ser.close()
    
    def check_queue(self):
        try:
            while True:
                action, data = self.data_queue.get_nowait()
                
                if action == 'WINNER':
                    # Schedule winner popup in main thread
                    self.root.after(0, lambda: self.show_winner(data))
                
                elif action == 'MOVE':
                    symbol, button_index = data
                    if 0 <= button_index < 9:
                        display_symbol = 'O' if symbol == '0' else 'X'
                        self.buttons[button_index].configure(
                            text=display_symbol,
                            state='disabled',
                            disabledforeground='black'
                        )
                        self.moves_count += 1
                        if self.moves_count == 9:
                            # Schedule draw check in main thread
                            self.root.after(0, self.check_draw)
                
                self.data_queue.task_done()
        except queue.Empty:
            pass
        
        if self.running:
            self.root.after(100, self.check_queue)
    
    def on_escape(self, event):
        self.on_closing()
    
    def on_closing(self):
        self.running = False
        self.root.destroy()
    
    def run(self):
        self.root.mainloop()

if __name__ == '__main__':
    app = ArduinoGUI()
    app.run()