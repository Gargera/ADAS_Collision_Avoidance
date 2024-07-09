# app.py
import tkinter as tk
from tkinter import messagebox

def on_button_click():
    messagebox.showinfo("Title", "Button clicked!")

root = tk.Tk()
root.title("Tkinter App")

button = tk.Button(root, text="Click Me", command=on_button_click)
button.pack(pady=20)

root.mainloop()
