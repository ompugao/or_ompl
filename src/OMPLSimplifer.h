/***********************************************************************

Copyright (c) 2014, Carnegie Mellon University
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

  Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*************************************************************************/
#ifndef OMPLSIMPLIFIER_H
#define OMPLPIMPLIFIER_H

#include <openrave-core.h>
#include <openrave/planner.h>
#include <openrave/planningutils.h>
#include <ompl/geometric/SimpleSetup.h>

#include "OMPLPlannerParameters.h"

namespace or_ompl
{

class OMPLSimplifier : public OpenRAVE::PlannerBase {
public:
    OMPLPlanner(OpenRAVE::EnvironmentBasePtr penv);
    virtual ~OMPLPlanner();

    virtual bool InitPlan(OpenRAVE::RobotBasePtr robot, PlannerParametersConstPtr params);
    virtual bool InitPlan(OpenRAVE::RobotBasePtr robot, std::istream& input);

    virtual OpenRAVE::PlannerStatus PlanPath(OpenRAVE::TrajectoryBasePtr ptraj);
    virtual PlannerParametersConstPtr GetParameters() const { return m_parameters; }
    ompl::geometric::SimpleSetupPtr GetSimpleSetup() { return m_simpleSetup; }
    ompl::base::StateSpacePtr GetStateSpace() { return m_stateSpace; }

private:
    OMPLPlannerParametersPtr m_parameters;
    ompl::geometric::SimpleSetupPtr m_simpleSetup;
    ompl::base::StateSpacePtr m_stateSpace;
    ompl::base::PlannerPtr m_planner;
    OpenRAVE::RobotBasePtr m_robot;
    OpenRAVE::CollisionReportPtr m_collisionReport;
    int m_numCollisionChecks;
    double m_totalCollisionTime;

    bool InitializePlanner();

    ompl::base::PlannerPtr OMPLPlanner::CreatePlanner(OMPLPlannerParameters const &params);
    bool IsStateValid(const ompl::base::State* state);
    bool IsInOrCollision(std::vector<double> jointValues);
    OpenRAVE::PlannerStatus ToORTrajectory(ompl::geometric::PathGeometric &ompl_traj,
                                           OpenRAVE::TrajectoryBasePtr or_traj) const;
};

typedef boost::shared_ptr<OMPLPlanner> OMPLPlannerPtr;

} /* namespace or_ompl */

#endif /* OMPLPLANNER_H_ */