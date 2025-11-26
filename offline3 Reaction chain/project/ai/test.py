
n = 9
m = 6

def check(board):
    board[0][0]["player"] = "hehe"
    
    
def again(board):
    board[0][0]["player"] = "again"
    
def printing(board):
    for i in range(n):
        for j in range(m):
            print(board[i][j], "")
        
        break
    

arr = [[{"player": 0 , "state": None } for i in range(m)] for j in range(n)]


printing(arr)

print()

check(arr)

printing(arr)





