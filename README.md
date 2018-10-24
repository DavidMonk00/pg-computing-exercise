# HEP Group PG Computing Exercise
## Installation Notes
### Prerequisites:
- Python analysis requires numpy and matplotlib libraries
- C++11 compatible compiler
### Clone repository
`git clone https://github.com/DavidMonk00/UROP-CMS-com-e.git`
### Crontab:
`crontab -e`:
```
* * * * * /path-to-folder/bin/main.py
0 * * * * /path-to-folder/bin/purge.py
