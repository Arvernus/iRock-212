# Branching 

## Feature Branches

Jedes neue Feature sollte sich auf seinem eigenen Branch befinden, der zu Sicherungs-/Zusammenarbeitszwecken zum zentralen Repository gepusht werden kann. Doch anstatt Branches auf Basis des main-Branch zu erstellen, nutzen feature-Branches den develop-Branch als übergeordneten Branch. Wenn ein Feature fertig ist, wird es zurück in den develop-Branch gemergt. Features sollten niemals direkt mit dem main-Branch interagieren.

## Git-flow-Workflow – Feature Branches

Beachte, dass die Kombination von Feature Branches mit dem develop-Branch eigentlich dem Feature Branch Workflow entspricht. Doch der Git-flow-Workflow geht darüber hinaus. feature-Branches werden für gewöhnlich auf Basis des aktuellsten develop-Branches erstellt.

![Branching Model](https://wac-cdn.atlassian.com/dam/jcr:34c86360-8dea-4be4-92f7-6597d4d5bfae/02%20Feature%20branches.svg?cdnVersion=1805)
