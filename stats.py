import matplotlib.pyplot as plt
import MySQLdb
import datetime
db = MySQLdb.connect(host="<censored>", user="<censored>", passwd="<censored>", db="<censored>")

class Attempt:
	def __init__(self, row):
		self.id=int(row[0])
		self.teamID=int(row[1])
		self.taskID=int(row[2])
		self.flag=row[3]
		self.result=row[4]==1
		self.passed=(row[5]-startTime).total_seconds()
		
	def __repr__(self):
		return str((self.id, self.teamID, self.taskID, self.flag, self.result, "%02d:%02d:%02d"%(self.passed/3600,self.passed%3600/60,self.passed%60)))
		
class Task:
	def __init__(self, row):
		self.id=row[0]
		self.point=row[1]
		self.nsolvers=0
		self.cat=row[2]
		
class Team:
	def __init__(self, row):
		self.id=row[0]
		self.name=unicode(row[1], errors='replace')
		self.point=0
		self.last=0
		self.points = [0]
		self.solved = []

teams = {}
cur = db.cursor()
cur.execute("SELECT `id`, `name` FROM `teams` ORDER BY `id`")
for row in cur.fetchall() :
    teams[int(row[0])]=Team(row)
cur.close()

tasks = {}
cur = db.cursor()
cur.execute("SELECT `id`, `point`, `cat` FROM `tasks` ORDER BY `id`")
for row in cur.fetchall() :
    tasks[int(row[0])]=Task(row)
cur.close()

startTime=0
cur = db.cursor()
cur.execute("SELECT `startTime` FROM `contest`")
startTime=cur.fetchone()[0]
startTime=datetime.datetime.fromtimestamp(startTime-7*60*60)
cur.close()

attempts=[]
cur = db.cursor()
cur.execute("SELECT * FROM `attempts` ORDER BY `id`")
for row in cur.fetchall():
	attempts.append(Attempt(row))
cur.close()

t=range(0,31)
for attempt in attempts:
	if attempt.passed<0:
		continue
	while attempt.passed/3600>teams[attempt.teamID].last+1:
		teams[attempt.teamID].points.append(teams[attempt.teamID].point)
		teams[attempt.teamID].last+=1
	if attempt.result and attempt.taskID not in teams[attempt.teamID].solved:
		teams[attempt.teamID].point+=tasks[attempt.taskID].point+2*max(0,3-tasks[attempt.taskID].nsolvers)
		tasks[attempt.taskID].nsolvers+=1
		teams[attempt.teamID].solved.append(attempt.taskID)
		
for key in teams:
	while len(teams[key].points)<len(t):
		teams[key].points.append(teams[key].point)

board=[]
for key in teams:
	board.append((teams[key].points, teams[key].name))
board.sort()
for b in board:
	print b
	
colors=[]
for i in range(4):
	for j in range(4):
		for k in range(4):
			colors.append((i*256/4,j*256/4,k*256/4))
			colors[-1] = "".join([hex(colors[-1][i])[2:] if colors[-1][i]>15 else '0'+hex(colors[-1][i])[2:] for i in range(3)])

i=0
for key in teams:
	team=teams[key]
	lines = plt.plot(t, team.points, marker='o', color='#'+colors[i], label=team.name)
	i+=1
plt.legend(bbox_to_anchor=(1.01, 1.11), loc=2, borderaxespad=0.)
plt.show()

