# Environment Configuration

## Register an EdgeImpulse Account
https://edgeimpulse.com/

## Install Edge Impulse CLI
- Install [Python 3](https://www.python.org/)

- Install [Node.js v14 or higher](https://nodejs.org/en/)
  If previously installed, check the version by running `node -v` in the PowerShell command line.

- Open PowerShell as an administrator
  ![installEICli](../resource/DocPic/installEICli.png)

- Install the Edge Impulse CLI tool by running the following command in PowerShell:
```bash
npm install -g edge-impulse-cli --force
```

## FAQ
**Q: Missing file error: `C:\Users\DFRobot\AppData\Roaming\npm\node_modules\edge-impulse-cli\build\cli\daemon.js`?**
A: Locate the `daemon.js` file, then move it to the specified path.

**Q: Error: `+CategoryInfo : SecurityError: (:) [], ParentContainsErrorRecordException +FullyQualifiedErrorId : UnauthorizedAccess`?**
A: Open PowerShell as an administrator and run the following command:
```bash
set-executionpolicy remotesigned
```
