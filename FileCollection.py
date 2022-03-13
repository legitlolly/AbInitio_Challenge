# This script will collect all filenames for all data files in the Data directory and save as a CSV
# this allows for variable amount of data files with no further work needed by the user

from os import listdir
import numpy as np
import pandas as pd

listdir = listdir("Data/")

j = 0
for i in listdir:
    listdir[j] = "Data/" + i
    j += 1

fileNames = np.array(listdir)
df = pd.DataFrame(fileNames)
df.append(df,)
df.to_csv("CSVFileNames.csv", header=False)
