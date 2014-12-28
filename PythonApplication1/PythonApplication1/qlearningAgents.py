# qlearningAgents.py
# ------------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *

import random,util,math

class QLearningAgent(ReinforcementAgent):
  """
    Q-Learning Agent

    Functions you should fill in:
      - getQValue
      - getAction
      - getValue
      - getPolicy
      - update

    Instance variables you have access to
      - self.epsilon (exploration prob)
      - self.alpha (learning rate)
      - self.discount (discount rate)

    Functions you should use
      - self.getLegalActions(state)
        which returns legal actions
        for a state
  """
  def __init__(self, **args):
    "You can initialize Q-values here..."
    ReinforcementAgent.__init__(self, **args)
    
    self.qvalues = util.Counter()
    #actions=self.getLegalActions(state)
    #for action in actions:
     # self.qvalues[state, action]=0
    

    "*** YOUR CODE HERE ***"
    

  def getQValue(self, state, action):
    """
      Returns Q(state,action)
      Should return 0.0 if we never seen
      a state or (state,action) tuple
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    
    if (state,action) in self.qvalues:
      return self.qvalues[(state,action)]
    else:
      return 0.0

  def getValue(self, state):
    """
      Returns max_action Q(state,action)
      where the max is over legal actions.  Note that if
      there are no legal actions, which is the case at the
      terminal state, you should return a value of 0.0.
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    r=None
    actions=self.getLegalActions(state)
    if (len(actions)==0): r=0
    for action in actions:
      qv=self.getQValue(state,action)
      if r == None or qv>r: r=qv
    return r  

  def getPolicy(self, state):
    """
      Compute the best action to take in a state.  Note that if there
      are no legal actions, which is the case at the terminal state,
      you should return None.
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    r = None
    b_action=None
    actions=self.getLegalActions(state)
    for action in actions:
      qv=self.getQValue(state,action)
      if r == None or qv > r: 
        b_action=action
        r=qv
    return b_action      

  def getAction(self, state):
    """
      Compute the action to take in the current state.  With
      probability self.epsilon, we should take a random action and
      take the best policy action otherwise.  Note that if there are
      no legal actions, which is the case at the terminal state, you
      should choose None as the action.

      HINT: You might want to use util.flipCoin(prob)
      HINT: To pick randomly from a list, use random.choice(list)
    """
    # Pick Action
    legalActions = self.getLegalActions(state)
    actionsToExplore = []
    
    for action in legalActions:
        if self.getQValue(state,action) == 0:
            actionsToExplore.append(action)
    
    action = None
    
    chooseRandom=util.flipCoin(self.epsilon)
   
    if (chooseRandom):
        if (len(actionsToExplore) > 0):
            action = random.choice(actionsToExplore)
        else:
            action = random.choice(legalActions)
    else:
      action=self.getPolicy(state)
    
    return action
    

  def update(self, state, action, nextState, reward):
    """
      The parent class calls this to observe a
      state = action => nextState and reward transition.
      You should do your Q-Value update here

      NOTE: You should never call this function,
      it will be called on your behalf
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    print state
    print " : "
    print nextState
    print " : "
    print reward
    self.qvalues[(state,action)]=self.getQValue(state,action)+self.alpha*(reward+self.discount*self.getValue(nextState)-self.getQValue(state,action))
    return self.qvalues[(state,action)]

class PacmanQAgent(QLearningAgent):
  "Exactly the same as QLearningAgent, but with different default parameters"

  def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
    """
    These default parameters can be changed from the pacman.py command line.
    For example, to change the exploration rate, try:
        python pacman.py -p PacmanQLearningAgent -a epsilon=0.1

    alpha    - learning rate
    epsilon  - exploration rate
    gamma    - discount factor
    numTraining - number of training episodes, i.e. no learning after these many episodes
    """
    args['epsilon'] = epsilon
    args['gamma'] = gamma
    args['alpha'] = alpha
    args['numTraining'] = numTraining
    self.index = 0  # This is always Pacman
    QLearningAgent.__init__(self, **args)

  def getAction(self, state):
    """
    Simply calls the getAction method of QLearningAgent and then
    informs parent of action for Pacman.  Do not change or remove this
    method.
    """
    action = QLearningAgent.getAction(self,state)
    self.doAction(state,action)
    return action


class ApproximateQAgent(PacmanQAgent):
  """
     ApproximateQLearningAgent

     You should only have to overwrite getQValue
     and update.  All other QLearningAgent functions
     should work as is.
  """
  def __init__(self, extractor='IdentityExtractor', **args):
    self.featExtractor = util.lookup(extractor, globals())()
    PacmanQAgent.__init__(self, **args)
    self.weights = util.Counter()

  def getQValue(self, state, action):
    """
      Should return Q(state,action) = w * featureVector
      where * is the dotProduct operator
    """
    total = 0
    features = self.featExtractor.getFeatures(state,action)
    for feature in features:
        if feature in self.weights:
            total += self.weights[feature] * features[feature]
        else:
            self.weights[feature] = 1
            total += features[feature]
    return total

  def update(self, state, action, nextState, reward):
    """
       Should update your weights based on transition
    """
    features = self.featExtractor.getFeatures(state,action)
    for feature in features:
        self.weights[feature] = self.weights[feature] + self.alpha*(reward + self.discount * self.getValue(nextState) - self.getQValue(state,action))*features[feature]

  def final(self, state):
    "Called at the end of each game."
    # call the super-class final method
    PacmanQAgent.final(self, state)

    # did we finish training?
    if self.episodesSoFar == self.numTraining:
      # you might want to print your weights here for debugging
      "*** YOUR CODE HERE ***"
      pass