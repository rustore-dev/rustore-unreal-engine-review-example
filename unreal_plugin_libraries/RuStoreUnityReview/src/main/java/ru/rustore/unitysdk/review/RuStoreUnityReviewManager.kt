package ru.rustore.unitysdk.review;

import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.sdk.core.tasks.OnCompleteListener
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.sdk.review.RuStoreReviewManager
import ru.rustore.sdk.review.RuStoreReviewManagerFactory
import ru.rustore.sdk.review.model.ReviewInfo

object RuStoreUnityReviewManager {

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
            return;
        }

        reviewManager.requestReviewFlow()
            .addOnCompleteListener(object : OnCompleteListener<ReviewInfo> {
                override fun onFailure(throwable: Throwable) {
                    listener.OnFailure(throwable)
                }

                override fun onSuccess(result: ReviewInfo) {
                    reviewInfo = result
                    listener.OnSuccess()
                }
            })
    }

    fun launchReviewFlow(listener: ReviewResponseListener) {
        if (!isInitialized) {
            listener.OnFailure(RuStoreException("Unknown error"))
            return;
        }

        reviewInfo?.let {
            reviewManager.launchReviewFlow(reviewInfo = it).addOnCompleteListener(object: OnCompleteListener<Unit> {
                override fun onFailure(throwable: Throwable) {
                    listener.OnFailure(throwable)
                }

                override fun onSuccess(result: Unit) {
                    listener.OnSuccess()
                }
            })
        }
    }
}
