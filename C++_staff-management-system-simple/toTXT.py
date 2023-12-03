import pandas as pd

df_info_list = pd.read_excel(r"D:\Programming\C++\staff-management-txt\empFile.xlsx")
with open(r"D:\Programming\C++\staff-management-txt\empFile.txt",'w') as f:
    for i in range(len(df_info_list)):
        details = []
        for j in range(len(df_info_list.iloc[i])):
            details.append(str(df_info_list.iloc[i,j]))
            detail = ' '.join(details)+'\n'
        f.writelines(detail)

print("hello world!")