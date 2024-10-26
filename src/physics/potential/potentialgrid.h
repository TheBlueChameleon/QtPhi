// #ifndef POTENTIALGRID_H
// #define POTENTIALGRID_H

// #include "base/coordinates/basegrid.h"

// namespace Physics
// {
//     class PotentialGrid : public Base::BaseGrid<Base::Scalar>
//     {

//         private:
//             void imposeImpl_noAcceleration(const PotentialGrid& potential, const Base::PixelCoordinate& minIdxs, const Base::PixelCoordinate& maxIdxs, const Base::PixelCoordinate& startIdxs);
//             void imposeImpl_avxAccelerated(const PotentialGrid& potential, const Base::PixelCoordinate& minIdxs, const Base::PixelCoordinate& maxIdxs, const Base::PixelCoordinate& startIdxs);

//         public:
//             PotentialGrid();
//             PotentialGrid(Base::PixelCoordinate size, Base::Real gridConstant, Base::Real level = 0);

//             Base::PixelCoordinate getMinimumImposeIndices(const PotentialGrid& potential, const Base::PixelCoordinate at) const;
//             Base::PixelCoordinate getMaximumImposeIndices(const PotentialGrid& potential, const Base::PixelCoordinate at) const;

//             void imposeAt(const PotentialGrid& potential, const Base::RealCoordinate  at);
//             void imposeAt(const PotentialGrid& potential, const Base::PixelCoordinate at);

//             std::string to_string() const;
//     };
// }

// #endif // POTENTIALGRID_H
