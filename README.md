# Github Instructions 
### Download/Clone repository
```
git clone https://github.com/path/to/repo.git
cd {Repository}
git status
```
**git status: This will show the branch you are on plus changes made.**
****

### Create your own Branch
**NEVER make changes directly to the master br!!!**
```
git checkout -b {Branch Name}
```
##### Branch naming convention goes as First Initial, Last Initial, Changes you will make to the Branch 
##### i.e for a person named John Smith working on adding graphics the branch should be named JS-AddGraphics
****

### Editing your Branch
Verify you are on your branch. From here on, any changes you make will affect only this branch. If you switch to the Master branch ```git checkout master```, git will automatically swap out the files and revert back to the state that the Master branch was in. Your changes to the other branch will also be saved and those files will be restored once you switch back to that branch ```git checkout {Branch Name}```


### Saving changes to your branch
```
git add . # If files deleted a -A may be necessary
git commit -m "Breif description of changes made"
git push origin {Branch Name}
```
**The first time you perform the "git-commit" action you may get an error looking for a global username and email, just follow the onscreen directions to resolve this problem.**


### Pulling changes from github repository
```git pull```
*or*
```git pull origin {Branch Name}```


### Merging Your branch with master
##### Update master branch with information on the git
```
git checkout master
git pull origin master
```

##### Merge in master with the branch
```
git checkout {Branch Name}
git merge master
# Fix merge conflicts
git add .
git commit -m "merge conConflict fixes"
git push origin {branch name}
```

##### Merge in the branch on GitHub
* Navigate to the repository on [GitHub](github.com)
* Locate your branch and create a pull request
* The other members will view the pull request and give you the thumbs up if it is good.
* Then you will merge the pull request and delete your branch
* Do not forget to pull down the new master branch on your local machine and delete branch there ```git branch -d {Branch Name}```
