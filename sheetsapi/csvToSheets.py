
from googleapiclient.discovery import build
import os.path
import pickle
from pprint import pprint
import pandas as pd
import time
import sys
import settingup as s
import os

# Loading credentials
# Gets path to API
def getPath():
    if os.path.exists('token.pickle'):

        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)

        service = build('sheets','v4',credentials=creds)
        return service

# Creates spreadsheet with primary as title
def createSpreadSheet(prim, service):
    spreadsheet_body ={
      "properties":
      {
        "title": prim
      }

    }

    request = service.spreadsheets().create(body=spreadsheet_body)
    response = request.execute()
    print("Spreadsheet URL: "  + response['spreadsheetUrl'])
    return response['spreadsheetId']

# Add tab for spreadsheet
def addSheet(spreadsheetId, s, data, service):


    resource = {
        'requests': [
                    {
                        'addSheet':{
                            'properties':{
                                'title': s

                            }

                        }
                    }
                ],

    }


    # Create sheet that belongs to spreadsheet
    resp = service.spreadsheets().batchUpdate(
        spreadsheetId=spreadsheetId,
        body=resource,
        ).execute()

    # Define body for sheet
    # Update
    # Must update for all rows of data
    for i in range(0, len(data)):

        res = {
            "majorDimension": "COLUMNS",
            "values": data[i]

        }
        time.sleep(5)
        service.spreadsheets().values().append(
        spreadsheetId=spreadsheetId, range=s+'!A1',
        body=res, valueInputOption='RAW').execute()


# Processes all the data and creates a map of primary's -> secondary dataframes to be tabs
def process(filename, service, delim, primary, secondary, cols):
    df = pd.read_csv(filename,sep=delim)


    df.sort_values(primary, inplace=True)
    # Create unique list of primary values
    UniquePrimIDs = df[primary].unique()
    # Sort by secondary
    df.sort_values(secondary, inplace=True)
    # Create a data frame dictionary to store your data frames
    target = {elem : df for elem in UniquePrimIDs}


    for key in target.keys():
        target[key] = df[:][df[primary] == key]

    # Run thru each df of primary key
    # Create new df to be tabs w/ unique secondary columns
    for id in target.keys():

        spreadsheetId = ''

        for i in range(0,len(target[id][primary])):
            prim = target[id][primary].values[i]
            print("Primary Target Added: " + str(prim))
            spreadsheetId = createSpreadSheet(str(prim), service)
            break

        # Unique list of secondary column values
        UniqueSecondary = target[id][secondary].unique()

        # Alphabetize list
        UniqueSecondary.sort()
        for tab in UniqueSecondary:

            tab_df = target[id][target[id][secondary] == tab]
            if tab_df.empty == False:
                print("Secondary Target Added: " + str(tab))

                tab_df = tab_df[cols]

                list = []
                column_names = []
                for col in cols:
                    l = [col]
                    column_names.append(l)

                list.append(column_names)

                for index, rows in tab_df.iterrows():
                    temp_list = []
                    for item in cols:

                        add_col = [rows[item]]
                        # Fill list with column values
                        temp_list.append(add_col)
                    # Fill list with row values
                    list.append(temp_list)
                addSheet(spreadsheetId, str(tab), list, service)

# Processes the dataframe and returns the dictionary of all columns
def getColumns(filename, delim):
    df = pd.read_csv(filename,sep=delim)
    listOfColumns = df.columns
    i = 1
    new_dict = dict()
    for elem in listOfColumns:
        new_dict[i] = elem
        i+=1
    return new_dict

# Prints all columns to chose primary
def printPrimary(dict):
    print("Primary options: ")
    for key in dict:
        print('(' + str(key) + ') ' + str(dict[key]))

# Prints out all columns
def printData(dict):
    print("Data options: ")
    for key in dict:
        print('(' + str(key) + ') ' + str(dict[key]))

# Prints out columns of csv without the already chosen primary column
def printSecondary(dict, prim):
    print("Secondary options: ")
    for key in dict:
        if prim != key:
            print('(' + str(key) + ') ' + str(dict[key]))

# Gets inoput file as csv for code to run
def getFile():
    files = [f for f in os.listdir('.') if os.path.isfile(f)]
    filedict = dict()
    ct = 1;
    for f in files:
        if '.csv' in f:
            filedict[ct] = f
            ct+=1
    printFiles(filedict)
    file = ''
    while file not in filedict:
        user_input = input("Enter valid key number for desired file: ")
        try:
            file = int(user_input)
        except ValueError:
            print("Not an integer... Please enter an integer")
    print("File: " + str(filedict[file])+ " succesfully chosen...")
    return(filedict[file])

# Outputs list of csvs files within directory
def printFiles(dict):
    if not dict:
        print("Looks like there are no CSVs to input... Make sure your desired input is in this folder!")
        exit()
    for key in dict:
        print('(' + str(key) + ') ' + str(dict[key]))

# Handles the processing oif the token.pickle file, setups api if there is no token
def token():
    files = [f for f in os.listdir('.') if os.path.isfile(f)]
    count = 0
    for f in files:
        if ".pickle" in f:
            count +=1
            print("Found token file with name " + str(f))
            print("Running script with " + str(f) + " as token... if incorrect press ^c to exit.")
            time.sleep(5)

    if count == 0:
        print("Token file not found... acquiring token now...")
        s.main()
        time.sleep(7)
    print("\n")

# Get value of primary column
def getPrimary(dict):
    primary = ''
    while primary not in dict:
        print("\n")
        printPrimary(dict)
        user_input =input("Enter a valid primary key: ")
        try:
            primary = int(user_input)
        except ValueError:
            print("Not an integer... Please enter an integer")
    print("Primary column: " + str(dict[primary]) + " chosen succesfully...")
    return dict[primary]

# Get the value of secondary column
def getSecondary(dict, primary):
    sec = ''
    while sec not in dict:
        print("\n")
        printSecondary(dict, primary)
        user_input =input("Enter a valid secondary key: ")
        try:
            sec = int(user_input)
        except ValueError:
            print("Not an integer... Please enter an integer")
    print("Secondary column: " + str(dict[sec]) + " chosen succesfully...")
    return dict[sec]

# Ask user for columns they want in ouput, returns list of column names
def getData(dict):
    data_points = []
    still_adding = True

    while still_adding:
        to_add = ''
        while to_add not in dict:
            print("\n")
            printData(dict)
            user_input = input("Enter desired data key: ")
            try:
                to_add = int(user_input)
                if dict[to_add] in data_points:
                    print("This column has already been added. Please enter a new data point. ")
                    to_add = ''
            except ValueError:
                print("Not an integer... Please enter an integer")
        print("Data column: " + str(dict[to_add]) + " added succesfully...")
        data_points.append(dict[to_add])
        more = input("Add another column? y or n: ")

        while more != 'y' and more != 'n':
            more = input("Response not in proper format? y for yes or n for no: ")

        if more == 'y':
            still_adding = True
        else:
            still_adding = False

    return data_points


def interact():
    print("MAKE SURE ALL FILES ARE IN SAME FOLDER :D")
    print("\n")

    token()

    file = getFile()

    delim = input("Enter delimiter: ")

    dict = getColumns(file, delim)

    primary = getPrimary(dict)

    secondary = getSecondary(dict, primary)

    if primary == secondary:
        print("\n")
        print("Both primary and secondary columns are the same... Please run again and avoid this!!!")
        exit()

    cols = getData(dict)

    service = getPath()

    process(file, service, delim, primary, secondary, cols)

def main():
    interact()

if __name__ == '__main__':
    main()
