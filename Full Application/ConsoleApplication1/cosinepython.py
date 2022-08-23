import pandas as pd
df=pd.read_csv("main1_data.csv")
file1 = open("finalfile.txt","r") 
x=file1.read()
file1.close()
movie_user_likes=x
df2 = {'director_name': '', 'actor_1_name': '', 'actor_2_name': '','actor_3_name':'','genres':'','movie_title':'','comb':movie_user_likes}
df = df.append(df2,ignore_index = True)
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity
cv=CountVectorizer()
count_matrix=cv.fit_transform(df["comb"])

cosine_sim=cosine_similarity(count_matrix)
Similar_movies= list(enumerate(cosine_sim[6010]))
sorted_similar_movies= sorted(Similar_movies,key= lambda x:x[1],reverse= True)[1:]
df['index'] = df.index

def get_title_from_index(index):
    return df[df.index==index]["movie_title"].values[0]
def get_index_from_title(title):
    return df[df.movie_title==title]["index"].values[0]
file2 = open("output.txt","w") 

i=0;
for element in sorted_similar_movies:
    file2.write(get_title_from_index(element[0]))
    file2.write('\n')
    i=i+1;
    if i>=21:
        break

file2.close()