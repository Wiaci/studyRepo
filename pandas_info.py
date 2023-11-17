import pandas as pd

df = pd.read_csv("https://raw.githubusercontent.com/evgpat/edu_stepik_first_step_in_nlp/main/datasets/telecom_churn.csv")

print(df.head())
print(df.shape)

df = df.drop('State', axis=1)

df['International plan'] = df['International plan'].map({
    'Yes': 1,
    'No': 0,
})

df['Churn'] = df['Churn'].astype(int)