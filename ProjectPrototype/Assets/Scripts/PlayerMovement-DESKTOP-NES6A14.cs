using UnityEngine;
using System.Collections;

public class PlayerMovement : MonoBehaviour {
	public float speed = 200f;            // The speed that the player will move at.
	
	Vector3 movement;                   // The vector to store the direction of the player's movement.
	Animator anim;                      // Reference to the animator component.
	Rigidbody playerRigidbody;          // Reference to the player's rigidbody.
	//Vector3 positionNow;				// player position

	NavMeshAgent agent;
	Vector3 toiletPt;
	Vector3 elevatePt;
	Vector3 hydrantPt;
	
	void Awake ()
	{
		
		// Set up references.
		anim = GetComponent <Animator> ();
		playerRigidbody = GetComponent <Rigidbody> ();
		//positionNow = transform.position;

		agent = GetComponent<NavMeshAgent>();
		elevatePt = new Vector3 (-954.2f, 0f, 148.6f);
		toiletPt = new Vector3 (-1335.4f, 0f, 363.2f);
		hydrantPt = new Vector3 (-2082.45f, 0f, -54f);
	}

	void LateUpdate() {
		Cardboard.SDK.UpdateState ();
		if (Cardboard.SDK.BackButtonPressed) {
			Application.Quit ();
		}
	}

	public void setToiletDest(){
		agent.SetDestination (toiletPt);
	}

	public void setElevatorDest(){
		agent.SetDestination (elevatePt);
	}

	public void setHydrantDest(){
		agent.SetDestination (hydrantPt);
	}
	
	
	void FixedUpdate ()
	{
		// Store the input axes.
		float h = Input.GetAxisRaw ("Horizontal");
		float v = Input.GetAxisRaw ("Vertical");
		v *= -1f;
		
		// Move the player around the scene.
		Move (h, v);
		
		// Animate the player.
		Animating (h, v);
	}
	
	void Move (float v, float h)
	{
		// Set the movement vector based on the axis input.
		movement.Set (h, 0f, v);
		
		// Normalise the movement vector and make it proportional to the speed per second.
		movement = movement.normalized * speed * Time.deltaTime;

		//positionNow = transform.position + movement;
		
		// Move the player to it's current position plus the movement.
		playerRigidbody.MovePosition (transform.position + movement);
	}

	
	void Animating (float h, float v)
	{
		// Create a boolean that is true if either of the input axes is non-zero.
		bool walking = h != 0f || v != 0f;
		
		// Tell the animator whether or not the player is walking.
		anim.SetBool ("IsWalking", walking);
	}
}
