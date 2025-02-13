/**
 * @file MessageIDs.h
 *
 * Declaration of ids for debug messages.
 *
 * @author Martin Lötzsch
 */

#pragma once

#include "Tools/Streams/Enum.h"

/**
 * IDs for debug messages
 *
 * To distinguish debug messages, they all have an id.
 */
GLOBAL_ENUM(MessageID,
{,
  undefined,
  idProcessBegin,
  idProcessFinished,

  idActivationGraph,
  idAlternativeRobotPoseHypothesis,
  idAnnotation,
  idAudioData,
  idBallModel,
  idBallPercept,
  idBallPerceptorEvaluation,
  idBallSpots,
  idBehaviorMotionRequest,
  idBehaviorStatus,
  idBodyContour,
  idCameraInfo,
  idCameraMatrix,
  idCirclePercept,
  idDropInPlayer,
  idFieldBoundary,
  idFieldColors,
  idFieldLines,
  idFieldLineIntersections,
  idFsrSensorData,
  idFrameInfo,
  idGameInfo,
  idGroundTruthOdometryData,
  idGroundTruthWorldState,
  idImage,
  idImageCoordinateSystem,
  idImagePatches,
  idInertialData,
  idInertialSensorData,
  idIntersectionsPercept,
  idJointAngles,
  idJointSensorData,
  idJPEGImage,
  idKeyStates,
  idLinesPercept,
  idLowFrameRateImage,
  idMotionInfo,
  idMotionRequest,
  idNetworkThumbnail,
  idObstacleModel,
  idObstacleModelCompressed,
  idOdometer,
  idOdometryData,
  idOpponentTeamInfo,
  idOwnTeamInfo,
  idPenaltyMarkPercept,
  idPlayersPercept,
  idRealisticBallPercepts,
  idReceivedSPLStandardMessages,
  idRobotHealth,
  idRobotInfo,
  idRobotPose,
  idScanlineRegions,
  idSelfLocalizationHypotheses,
  idSideConfidence,
  idSPLStandardBehaviorStatus,
  idStopwatch,
  idSystemSensorData,
  idTeamBallModel,
  idTeammateData,
  idTeammateReliability,
  idTeamPlayersModel,
  idThumbnail,

  numOfDataMessageIDs, /**< everything below this does not belong into log files */

  // ids used in team communication
  idFieldFeatureOverview = numOfDataMessageIDs,
  idNTPHeader,
  idNTPIdentifier,
  idNTPRequest,
  idNTPResponse,
  idRobot,
  idTeam,
  idTeammateBallAge,
  idTeammateHasGroundContact,
  idTeammateIsPenalized,
  idTeammateIsUpright,
  idTeammateRoles,
  idTeammateTimeOfLastGroundContact,
  idTeammateFieldCoverage,
  idWhistle,

  // infrastructure
  idConsole,
  idDebugDataChangeRequest,
  idDebugDataResponse,
  idDebugDrawing,
  idDebugDrawing3D,
  idDebugImage,
  idDebugJPEGImage,
  idDebugRequest,
  idDebugResponse,
  idDrawingManager,
  idDrawingManager3D,
  idJointCalibration,
  idJointRequest,
  idLogResponse,
  idModuleRequest,
  idModuleTable,
  idMotionNet,
  idPlot,
  idQueueFillRequest,
  idRobotDimensions,
  idRobotname,
  idStreamSpecification,
  idText,
  idUSRequest,
  idColorCalibration,
  idWalkingEngineKick,
  
  // team communication
  idKeeperKick,
  idStrikerKick,
  idSupporterKick,
  idDefenderKick,
  idStabberKick,

  idRole,

  idKeeperBehavior,
  idStrikerBehavior,
  idSupporterBehavior,
  idDefenderBehavior,
  idStabberBehavior,
});
