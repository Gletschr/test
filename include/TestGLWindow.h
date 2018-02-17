#ifndef TESTGLWINDOW_H
#define TESTGLWINDOW_H

#include <QColor>
#include <QPointF>
#include <QVector>
#include <QOpenGLWindow>

///
/// \brief App main window.
///
class TestGLWindow : public QOpenGLWindow {

public:

	///
	/// \brief Constructor.
	///
	explicit TestGLWindow();

	///
	/// \brief Destructor.
	///
	virtual ~TestGLWindow();

	///
	/// \brief Load and prepare resources for rendering.
	///
	void loadAndPrepareRenderResources();

private:

	void drawPoint(const QPointF &point, const QColor &color);
	void drawContour(const QVector<QPointF> &contour, const QColor &color);

private:

	QColor faceColor;

	QColor centroidColor;

	QColor originEyeColor;
	QColor scaledEyeColor;
	QColor rotatedEyeColor;

	QPointF faceCentroid;

	QVector<QPointF> faceContour;

	QVector<QPointF> leftEyeOriginContour;
	QVector<QPointF> rightEyeOriginContour;

	QVector<QPointF> leftEyeScaledContour;
	QVector<QPointF> rightEyeScaledContour;

	QVector<QPointF> leftEyeRotatedContour;
	QVector<QPointF> rightEyeRotatedContour;

protected: // QOpenGLWindow overrides.

	virtual void initializeGL() Q_DECL_OVERRIDE;
	virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	virtual void paintGL() Q_DECL_OVERRIDE;

};

#endif // TESTGLWINDOW_H
