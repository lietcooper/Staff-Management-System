import pandas as pd

info_list = []
with open(r"D:\Programming\C++\staff-management-txt\empFile.txt", 'r') as f:
    while True:
        line = f.readline()
        if not line:
            break

        info_list.append(line.strip().split(' '))
        # print(info_list)
df_info_list = pd.DataFrame(info_list,
                            columns=['ID', 'Name', 'Gender', 'depID', 'Birthday', 'Politics Status', 'Email'])
pd.DataFrame(df_info_list).to_excel(r"D:\Programming\C++\staff-management-txt\empFile.xlsx", sheet_name='Staff',
                                    index=False, header=True)