using UnityEngine;
using System.Collections;

//[RequireComponent(typeof(Collider))]
public class PlayerMovement : MonoBehaviour{

	public float speed = 200f;            // The speed that the player will move at.
	//public float rotateSpeed = 1f;
	//public float dirObjDist = 5f;
	Vector3 movement;                   // The vector to store the direction of the player's movement.
	//Vector3 direction, directionOrth;
	Rigidbody playerRigidbody;          // Reference to the player's rigidbody.
	//float theta;
	//GameObject directionObj;
	Vector3 position;

	NavMeshAgent agent;
	Vector3 toiletPt;
	Vector3 elevatePt;
	Vector3 hydrantPt;

	void Awake ()
	{

		// Set up references.
		playerRigidbody = GetComponent <Rigidbody> ();
		//theta = Mathf.PI/2;
		//directionObj = GameObject.Find ("Direction");
		position = transform.position;

		agent = GetComponent<NavMeshAgent>();
		elevatePt = new Vector3 (-954.2f, 0f, 148.6f);
		toiletPt = new Vector3 (-1335.4f, 0f, 363.2f);
		hydrantPt = new Vector3 (-2082.45f, 0f, -54f);
	}

	/*
	void LateUpdatye(){
		GvrViewer.Instance.UpdateState ();
		if (GvrViewer.Instance.BackButtonPressed){
			Application.Quit ();
		}
	}
	*/


	public void setToiletDest(){
		//agent.SetDestination (toiletPt);
		position = toiletPt;
		Debug.Log ("Set toiletPt");
	}

	public void setElevatorDest(){
		//agent.SetDestination (elevatePt);
		position = elevatePt;
		Debug.Log ("Set elevatePt");
	}

	public void setHydrantDest(){
		//agent.SetDestination (hydrantPt);
		position = hydrantPt;
		Debug.Log ("Set hydrantPt");
	}

	void FixedUpdate ()
	{
		// Store the input axes.
		float h = Input.GetAxisRaw ("Horizontal");
		float v = Input.GetAxisRaw ("Vertical");
		v *= -1;
		Debug.Log (h.ToString () + " " + v.ToString ());

		/*
		if (h==0&&v==0) {
			Debug.Log ("position");
			position = transform.position;
		}
		*/
		/*
		if (Input.GetKeyDown (KeyCode.LeftShift)) {
			theta += rotateSpeed*Time.deltaTime;
			h = 0;
			v = 0;
		}
		*/


		// Move the player around the scene.
		Move (h, v);

	}

	void Move (float v, float h)
	{
		// Set the movement vector based on the axis input.
		movement.Set (h, 0f, v);
		//movement.Set (0f, 0f, 0f);

		//direction.Set (Mathf.Cos(theta), 0f, Mathf.Sin(theta));
		//directionOrth.Set(Mathf.Cos(theta+Mathf.PI/2),0f,Mathf.Sin(theta+Mathf.PI/2));

		//Debug.Log ("direction Vector: " + direction.x.ToString () + " " + direction.y.ToString () + " " + direction.z.ToString () + "\n"
		//+ "direction orthogonal Vector: " + directionOrth.x.ToString () + " " + directionOrth.y.ToString () + " " + directionOrth.z.ToString ());
			

		//movement = h * direction + v * directionOrth;
		// Normalise the movement vector and make it proportional to the speed per second.
		movement = movement.normalized * speed * Time.deltaTime;
		// Move the player to it's current position plus the movement.
		//playerRigidbody.MovePosition (transform.position + movement);
		position = position + movement;
		agent.SetDestination (position);
		Debug.Log ("movement Vector: " + movement.x.ToString () + " " + movement.y.ToString () + " " + movement.z.ToString ());

		//direction = direction.normalized;
		//direction.y = 2f;
		//directionObj.transform.position = direction + transform.position;


	}

	/*
	#region IGvrGazeResponder implementation

	public void OnGazeEnter(){
	}

	public void OnGazeExit(){
	}

	public void OnGazeTrigger(){

	}

	#endregion
	*/
}
