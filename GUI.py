import customtkinter as ctk
import json



currentScore = 30


ctk.set_appearance_mode("System")  # Modes: system (default), light, dark
ctk.set_default_color_theme("blue")  # Themes: blue (default), dark-blue, green

app = ctk.CTk()  # create CTk window like you do with the Tk window
app.geometry("1440x1024")
canvas = ctk.CTkCanvas(app, width=500, height=480,highlightthickness=0,)
canvas.config(background="white")
canvas.place(x=0,y=0)


names = ["one","two","three","four","five"]
scores = [1,2,3,4,5]

def placeLeaderboard():
    canvas.create_rectangle(0, 0, 500, 500, fill="grey20", width=2) #grey14 to match background
    
    intx =  0
    inty = 80
    for i in range(len(names)):
        label1 = ctk.CTkLabel(width=249,height=79,text_color="white",text=names[i], font=("Arial",30),master=app)
        label1.place(x=intx,y=inty)
        label2 = ctk.CTkLabel(width=249,height=79,text_color="white",text=scores[i], font=("Arial",30),master=app)
        label2.place(x=intx+250,y=inty)
        inty+=80
    LEADERBOARD = ctk.CTkLabel(width=499,height=79,text_color="white",text="Leaderboard", font=("Arial",50),master=app)
    LEADERBOARD.place(x=0,y=0)
    StartButton = ctk.CTkButton(width=400,height=150,text="START",fg_color="green",corner_radius=50,font=("Arial",50),text_color="gray99",master=app)
    StartButton.place(x=50,y=600)
    ResetButton = ctk.CTkButton(width=400,height=150,text="RESET",fg_color="orange2",corner_radius=50,font=("Arial",50),text_color="gray99", master=app)
    ResetButton.place(x=50,y=800)
    scoreTitle = ctk.CTkLabel(width=50,height=20,text_color="white",text="Current Score:", font=("Arial",50),master=app)
    scoreTitle.place(x=600, y=20)
    scoreLabel = ctk.CTkLabel(width=50,height=20,text_color="white",text=currentScore, font=("Arial",50),master=app)
    scoreLabel.place(x=740, y=100)
    nameEntry = ctk.CTkEntry(width=350,height=50,master=app,font=("Arial",50))
    nameEntry.place(x=600,y=200)
    nameEntryButton = ctk.CTkButton(width=50,height=50,text="ENTER",fg_color="green",font=("Arial",20),text_color="gray99", master=app)
    nameEntryButton.place(x=980,y=205)
    panel = ctk.CTkImage(image = "Bell Drawing", master=app)
    panel.place(x=600,y=600)

placeLeaderboard()



#label = customtkinter.CTkLabel(app, text=f"Current Highest Record is: {highestRecord} | this was acomplished by: {highestRecordName}", fg_color="brown")
#progressbar = customtkinter.CTkProgressBar(app, height=300,orientation="vertical",width=40,fg_color="blue",progress_color="green",mode='determinate')

#progressbar.set(float(f"0.{highestRecord}"))

#label.grid(column=0,row=0)
#progressbar.grid(column=25,row=8)

app.mainloop()


