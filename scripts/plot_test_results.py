#!/usr/bin/python3

"""hash_table
    Copyright 2023 Debby Nirwan
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
"""

import pandas as pd
import plotly.express as px

insert_x = []
insert_lib_name = []
insert_time = []

insert_data = {
    "number of elements": insert_x,
    "library name": insert_lib_name,
    "time (us)": insert_time
}

at_x = []
at_lib_name = []
at_time = []

at_data = {
    "number of elements": at_x,
    "library name": at_lib_name,
    "time (us)": at_time
}

remove_x = []
remove_lib_name = []
remove_time = []

remove_data = {
    "number of elements": remove_x,
    "library name": remove_lib_name,
    "time (us)": remove_time
}


with open('test_results.txt') as f:
    for line in f:
        x = line.find("cpu time for")
        y = line.find("elements:")
        z = line.find("us")

        element_start_index = x + 13
        element_end_index = y-1
        element = int(line[element_start_index: element_end_index])

        time_start_index = y+10
        time_end_index = z-1
        time = int(float(line[time_start_index: time_end_index]))

        if "unordered_map" in line:
            if "insert()" in line:
                insert_x.append(element)
                insert_lib_name.append("unordered_map")
                insert_time.append(time)
            elif "at()" in line:
                at_x.append(element)
                at_lib_name.append("unordered_map")
                at_time.append(time)
            else:
                remove_x.append(element)
                remove_lib_name.append("unordered_map")
                remove_time.append(time)
        else:
            if "insert()" in line:
                insert_x.append(element)
                insert_lib_name.append("hash_table")
                insert_time.append(time)
            elif "at()" in line:
                at_x.append(element)
                at_lib_name.append("hash_table")
                at_time.append(time)
            else:
                remove_x.append(element)
                remove_lib_name.append("hash_table")
                remove_time.append(time)


insert_data_df = pd.DataFrame(insert_data)
at_data_df = pd.DataFrame(at_data)
remove_data_df = pd.DataFrame(remove_data)

fig = px.line(remove_data_df, log_x=True, markers=True, title="Remove element time performance",
              x="number of elements", y="time (us)", color="library name")
fig.show()
