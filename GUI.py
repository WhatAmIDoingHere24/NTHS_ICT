import customtkinter
import _json
import simplepyble


highestRecord = 30
highestRecordName = "jett"

customtkinter.set_appearance_mode("System")  # Modes: system (default), light, dark
customtkinter.set_default_color_theme("blue")  # Themes: blue (default), dark-blue, green

app = customtkinter.CTk()  # create CTk window like you do with the Tk window
app.geometry("500x500")



label = customtkinter.CTkLabel(app, text=f"Current Highest Record is: {highestRecord} | this was acomplished by: {highestRecordName}", fg_color="brown")
progressbar = customtkinter.CTkProgressBar(app, height=300,orientation="vertical",width=40,fg_color="blue",progress_color="green",mode='determinate')

progressbar.set(float(f"0.{highestRecord}"))

label.grid(column=0,row=0)
progressbar.grid(column=25,row=8)

app.mainloop()


