from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "peopleCount"
cnt = "count"
ae2 = "Light"
cnt2 = "level"
ae3="userInput"
cnt3="input"
# delete(uri_cse+"/"+ae+"/"+cnt+"/?rcn=4")
# delete(uri_cse+"/"+ae2+"/"+cnt2+"/?rcn=4")
# delete(uri_cse+"/"+ae3+"/"+cnt3+"/?rcn=4")

def create(ae,cnt):
    # create_ae(uri_cse, ae)
    uri_ae = uri_cse + "/" + ae
    # create_cnt(uri_ae, cnt)
    uri_cnt = uri_ae + "/" + cnt
    # create_data_cin(uri_cse+"/userInput/input", "0")

create(ae,cnt)
create(ae2,cnt2)
create(ae3,cnt3)