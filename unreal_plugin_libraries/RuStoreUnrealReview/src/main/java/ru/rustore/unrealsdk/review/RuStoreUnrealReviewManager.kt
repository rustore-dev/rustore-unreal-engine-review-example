package ru.rustore.unrealsdk.review;

import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.unrealsdk.core.PlayerProvider
import ru.rustore.sdk.review.RuStoreReviewManager
import ru.rustore.sdk.review.RuStoreReviewManagerFactory
import ru.rustore.sdk.review.model.ReviewInfo

object RuStoreUnrealReviewManager {

    private lateinit var reviewManager: RuStoreReviewManager
    private var reviewInfo: ReviewInfo? = null

    private var isInitialized:Boolean = false

    fun init(metricType: String) {
        PlayerProvider.getCurrentActivity()?.run {
            reviewManager = RuStoreReviewManagerFactory.create(
                context = application,
                internalConfig = mapOf("type" to metricType)
            )
            isInitialized = true
        }
    }

    fun requestReviewFlow(listener: ReviewResponseListener) {
        if (!isInitialized) {
            listener.OnFailure(RuStoreException("Unknown error"))
            return
        }

        reviewManager.requestReviewFlow()
            .addOnSuccessListener { result ->
                reviewInfo = result
                listener.OnSuccess()
            }
            .addOnFailureListener { throwable ->
                listener.OnFailure(throwable)
            }
    }

    fun launchReviewFlow(listener: ReviewResponseListener) {
        if (!isInitialized) {
            listener.OnFailure(RuStoreException("Unknown error"))
            return
        }

        reviewInfo?.let {
            reviewManager
                .launchReviewFlow(reviewInfo = it)
                .addOnSuccessListener {
                    listener.OnSuccess()
                }
                .addOnFailureListener { throwable ->
                    listener.OnFailure(throwable)
                }
        } ?: run {
            listener.OnFailure(RuStoreException("Review info not available. Call requestReviewFlow first."))
        }
    }
}
