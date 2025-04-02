import customtkinter
import json
import simplepyble
import sys
import pygame


#setup BLE
bleAdapters = simplepyble.Adapter.get_adapters()

if len(bleAdapters) == 0:
    print("no BLE adapters found")

print("select an adpater to use:")
for i, adapter in enumerate(bleAdapters):
    print(f"{i}: {adapter.identifier()} [{adapter.address()}]")

bleChoiceAdapter = int(input("Enter Adpater To use: "))
adapter = bleAdapters[bleChoiceAdapter]

print(f"youve selcted to use: {adapter.ifentifier()} [{adapter.address()}]")



# Recive JSON data over BLE



# parse JSON data into python dih
mpuData = json.loads(rxData)

pygame.mixer.init()
pygame.mixer.music.load('song.mp3')



highestRecord = 100
highestRecordName = "name"

customtkinter.set_appearance_mode("System")  # Modes: system (default), light, dark
customtkinter.set_default_color_theme("blue")  # Themes: blue (default), dark-blue, green

app = customtkinter.CTk()  # create CTk window like you do with the Tk window
app.geometry("340x340")

if highestRecord >= 100 :
    #play sound
    pygame.mixer.music.play(start=14,fade_ms=300)



label = customtkinter.CTkLabel(app, text=f"Current Highest Record is: {highestRecord} by: {highestRecordName}", fg_color="brown")
progressbar = customtkinter.CTkProgressBar(app, height=300,orientation="vertical",width=40,fg_color="blue",progress_color="green",mode='determinate')

progressbar.set(float(f"0.{highestRecord}"))

label.grid(column=0,row=0)
progressbar.grid(column=0,row=8)

app.mainloop()


