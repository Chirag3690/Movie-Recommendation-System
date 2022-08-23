import pandas as pd
from fuzzywuzzy import fuzz
from fuzzywuzzy import process
file1 = open("myfile.txt","r") 
x=file1.read()
file1.close()
df=pd.read_csv("main1_data.csv")

highest = process.extractOne(x,df["movie_title"].to_list())



df['index'] = df.index

def get_title_from_index(index):
    return df[df.index==index]["movie_title"].values[0]

def get_comb_from_index(index):
    return df[df.index==index]["comb"].values[0]
def get_index_from_title(title):
    return df[df.movie_title==title]["index"].values[0]

f=get_index_from_title(highest[0])

print("DO YOU MEAN : ")
print(highest[0])
file3=open("title.txt","w")
file3.write(highest[0])

y=get_comb_from_index(f)
file3.close()
file2 = open("myfile1.txt","w") 
file2.write(y)
file2.close()
