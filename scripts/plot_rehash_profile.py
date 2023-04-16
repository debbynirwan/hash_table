#!/usr/bin/python3

import pandas as pd
import plotly.express as px

element_index = []
bucket_count = []
time = []
lib_name = []

data = {
    "i-th element": element_index,
    "bucket count": bucket_count,
    "time (us)": time,
    "library name": lib_name
}

with open('rehash_profile.txt') as f:
    for line in f:
        i = line.find("i: ")
        t = line.find("time: ")
        s = line.find("size: ")
        e = line.find("\n")

        i_start_index = i + 3
        i_end_index = t-1
        try:
            ith = int(float(line[i_start_index: i_end_index]))
        except:
            print(line)
            continue

        t_start_index = t + 6
        t_end_index = s-1
        try:
            t_time = int(float(line[t_start_index: t_end_index]))
        except:
            print(line)
            continue

        s_start_index = s + 6
        s_end_index = e
        try:
            bc = int(float(line[s_start_index: s_end_index]))
        except:
            print(line)
            continue

        if "unordered_map" in line:
            lib_name.append("unordered_map")
        else:
            lib_name.append("hash_table")
        element_index.append(ith)
        bucket_count.append(bc)
        time.append(t_time)


df = pd.DataFrame(data)
fig = px.line(df, log_x=True, markers=True, title="Insert Profile - Time",
              x="i-th element", y="time (us)", color="library name")
fig.show()
