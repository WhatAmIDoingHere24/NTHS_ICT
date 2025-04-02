import customtkinter as ctk
import serial
import json

bt_serial = serial.Serial("COM1", 115200, timeout=2)

score = 0
highest_record = 0
highest_record_name = ""
nameList = [""]
scoreList = [0]

window = ctk.CTk()
window.title("Paddle Software")
window.geometry("1920x1080")

window.mainloop()