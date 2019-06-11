import json
import requests

#math to check if arbitrage is feasible
#if it is, return true
#else false
def checkOdds(odds1, odds2):
    totalOdds = odds1 + odds2

    if totalOdds <= 1:
        return True

    else:
        return False

def findStakes(odds1, odds2):
    #Individual stakes = (Investment x Individual Arbitrage %) / Total Arbitrage %
    #assume investment is always $100

    total = odds1 + odds2

    toBetOne = ((100 * odds1) / total)

    toBetTwo = ((100 * odds2) / total)

    returnList = [toBetOne, toBetTwo]

    return returnList

def convertToProbability(decimal):
    toReturn = (1/decimal)
    return toReturn

def findProfit(totalArb):
    #profit = (Investment / Arbitrage %) – Investment
    toReturnProfit = (100/totalArb) - 100


api_key = '4193cc1a899584858bede5d9cd497ccd'

#list of all active sport keys to traverse all available us odds
sports_response = requests.get( 'https://api.the-odds-api.com/v3/sports', params={
    'api_key': api_key,
    })

sports_json = json.loads(sports_response.text)

# add for loop that goes through all sports and checks their odds so that not just live/upcoming
for i in range(0, len(sports_json['data'])):
    # print(sports_json['data'][i]['key'])
    sport_key = sports_json['data'][i]['key']
    odds_response = requests.get('https://api.the-odds-api.com/v3/odds', params={
        'api_key': api_key,
        'sport': sport_key,
        'region': 'us',  # uk | us | au
        'mkt': 'h2h'  # h2h | spreads | totals

    })
    odds_json = json.loads(odds_response.text)
    if not odds_json['success']:
        print(
            'There was a problem with the odds request:',
            odds_json['msg']
        )

    else:
        print()
        print(
            'Successfully got {} events'.format(len(odds_json['data'])) + " in " + sports_json['data'][i]['key'] ,
            
        )

    # go through all responses to each sports call.


    for j in range(0, len(odds_json['data'])):

        # print(odds_json['data'][j]['teams'])
        #run through all american sites

        #need one loop for each site to run through other sites

        #first loop goes through each site as first team, checks if works with other team on all other sites
        for k in range(0, len(odds_json['data'][j]['sites'])):

            #decimal form
            # print(odds_json['data'][j]['sites'][k])
            firstOdds = convertToProbability(odds_json['data'][j]['sites'][k]['odds']['h2h'][0])

            # second loop that traverses all site pairs to see if arbitrage is possible

            for l in range(0, len(odds_json['data'][j]['sites'])):


                #decimal form
                secondOdds = convertToProbability(odds_json['data'][j]['sites'][l]['odds']['h2h'][1])

                #check if arb is possible...
                if(checkOdds(firstOdds, secondOdds)):
                    
                    print(odds_json['data'][j]['teams'][0] + " at " + str(odds_json['data'][j]['sites'][k]['odds']['h2h'][0]) + 
                        " on the site " + str(odds_json['data'][j]['sites'][k]['site_nice']))
                    print(odds_json['data'][j]['teams'][1] + " at " + str(odds_json['data'][j]['sites'][l]['odds']['h2h'][1]) + 
                        " on the site " + str(odds_json['data'][j]['sites'][l]['site_nice']))
                    print(firstOdds + secondOdds)
                    #find stakes for each parties
                    # stakes = findStakes(firstOdds, secondOdds)

                    #find profits
                    # totalArbitrage = firstOdds + secondOdds
                    # profit = findProfit(totalArbitrage)


                else:
                    continue























        
   