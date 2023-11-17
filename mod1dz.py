import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split

df = pd.read_csv("https://raw.githubusercontent.com/evgpat/edu_stepik_first_step_in_nlp/main/datasets/telecom_churn.csv")
print(df.shape)

df = df.drop('State', axis=1)
#print(df.head())

df['International plan'] = df['International plan'].map({
    'Yes': 1,
    'No': 0,
})

df['Voice mail plan'] = df['Voice mail plan'].map({
    'Yes': 1,
    'No': 0,
})

df['Churn'] = df['Churn'].astype(int)

print(df.head())

X = df.drop('Churn', axis=1)
y = df['Churn']

s = 0
for i in y:
    if i == 1:
        s += 1
print(s)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=123)
